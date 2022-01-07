/*
 * Copyright (C) EdgeTX
 *
 * Based on code named
 *   opentx - https://github.com/opentx/opentx
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "radio_sdmanager.h"
#include "opentx.h"
#include "libopenui.h"
#include "io/frsky_firmware_update.h"
#include "io/multi_firmware_update.h"
#include "io/bootloader_flash.h"
#include "standalone_lua.h"
#include "sdcard.h"
#include "view_text.h"
#include "file_preview.h"

#include <algorithm>

// todo: nested class
class FileNameEditWindow : public Page
{
  public:
  explicit FileNameEditWindow(const char* const iName) :
      Page{ICON_RADIO_SD_MANAGER}, name{iName}
  {
    buildHeader(&header);
    buildBody(&body);
  }

#if defined(DEBUG_WINDOWS)
  std::string getName() const override { return "FileNameEditWindow"; }
#endif

    private:
  const char* const name;

  void buildHeader(Window *window)
  {
    new StaticText(window, {PAGE_TITLE_LEFT, PAGE_TITLE_TOP + 10, LCD_W - PAGE_TITLE_LEFT, PAGE_LINE_HEIGHT}, STR_RENAME_FILE, 0, COLOR_THEME_PRIMARY2);
  }

  void buildBody(Window *window)
  {
    GridLayout grid(window);
    grid.spacer(8);
    uint8_t nameLength{0};
    uint8_t extLength{0};
    const char* const ext = getFileExtension(name, 0, LEN_FILE_EXTENSION_MAX, &nameLength, &extLength);
    if (ext) {
        originalName.clear().add(name, ext);
    }
    else {
        originalName.clear().add(name);
    }

    auto newFileName = new TextEdit(window, grid.getSlot(), originalName.raw(), originalName.capacity() - 1 - extLength, LcdFlags(0)); 
    newFileName->setChangeHandler([this, ext, extLength]() mutable {
        originalName.revalidate();
        if (originalName.free() >= extLength) {
            originalName.add(ext);
            f_rename((const TCHAR *)name, (const TCHAR *)originalName);
        }
    });
  }
private:
  name_t originalName{reusableBuffer.sdManager.nameBuffer};  
};

RadioSdManagerPage::RadioSdManagerPage() :
  PageTab(SD_IS_HC() ? STR_SDHC_CARD : STR_SD_CARD, ICON_RADIO_SD_MANAGER)
{
  setOnSetVisibleHandler([this]() {
    TRACE("f_chdir(ROOT_PATH)");
    f_chdir(ROOT_PATH);
    currentDir.clear().add(ROOT_PATH);
  });
}

void RadioSdManagerPage::rebuild(FormWindow * window)
{
  coord_t scrollPosition = window->getScrollPositionY();
  window->clear();
  build(window);
  window->setScrollPositionY(scrollPosition);
}

template <class T>
class FlashDialog: public FullScreenDialog
{
  public:
    explicit FlashDialog(const T & device):
      FullScreenDialog(WARNING_TYPE_INFO, "Flash device"),
      device(device),
      progress(this, {LCD_W / 2 - 50, LCD_H / 2, 100, 15})
    {
      setFocus();
    }

    void deleteLater(bool detach = true, bool trash = true) override
    {
      if (_deleted)
        return;

      progress.deleteLater(true, false);
      FullScreenDialog::deleteLater(detach, trash);
    }

    void flash(const char * filename)
    {
      TRACE("flashing '%s'", filename);
      device.flashFirmware(
          filename,
          [this](const char *title, const char *message, int count,
              int total) -> void {
            setMessage(message);
            progress.setValue(total > 0 ? count * 100 / total : 0);
            MainWindow::instance()->run(false);
          });
      deleteLater();
    }

  protected:
    T device;
    Progress progress;
};

class SDmanagerButton : public TextButton
{
  public:
    SDmanagerButton(FormGroup* parent, const rect_t& rect, std::string text,
              std::function<uint8_t(void)> pressHandler = nullptr,
              WindowFlags windowFlags = BUTTON_BACKGROUND | OPAQUE,
              LcdFlags textFlags = 0 ) : TextButton(parent, rect, text, pressHandler, windowFlags, textFlags)
              {
              }; 
#if defined(HARDWARE_TOUCH)
  bool onTouchStart(coord_t x, coord_t y) override
  {
    if (enabled) {
      if (!(windowFlags & NO_FOCUS)) {
        setFocus(SET_FOCUS_DEFAULT);
      }
    }
    return true;
  }
#endif              
};

void RadioSdManagerPage::updateCurrentDir(){
    currentDir.fillRaw([this](char* s){
        f_getcwd(s, currentDir.capacity());        
    });    
}

bool RadioSdManagerPage::fileExists(const char* const filename) {
    FILINFO finfo;
    return (f_stat(filename, &finfo) == FR_OK);
}

void RadioSdManagerPage::build(FormWindow * const window) {
  updateCurrentDir();    
  FormGridLayout grid;
  grid.spacer(PAGE_PADDING);

  FILINFO fno;
  DIR dir;
  std::list<std::string> files;
  std::list<std::string> directories;
  
  auto const preview = new FilePreview(window, {LCD_W / 2 + 6, 0, LCD_W / 2 - 16, window->height()});

  FRESULT res = f_opendir(&dir, "."); // Open the directory
  if (res == FR_OK) {
    // read all entries
    bool firstTime = true;
    for (;;) {
      res = sdReadDir(&dir, &fno, firstTime);

      if (res != FR_OK || fno.fname[0] == 0)
        break; // Break on error or end of dir
      if (strlen((const char*)fno.fname) > SD_SCREEN_FILE_LENGTH)
        continue;
      if (fno.fname[0] == '.' && fno.fname[1] != '.')
        continue; // Ignore hidden files under UNIX, but not ..

      if (fno.fattrib & AM_DIR) {
        directories.push_back((char*)fno.fname);
      } else {
        files.push_back((char*)fno.fname);
      }
    }

    // sort directories and files
    directories.sort(compare_nocase);
    files.sort(compare_nocase);
    
    for (const auto& dname: directories) {
      new SDmanagerButton(window, grid.getLabelSlot(), dname, [this, dname, window]() -> uint8_t {
          currentDir.add(PATH_SEPARATOR).add(dname);
          f_chdir((const TCHAR*)currentDir);
          window->clear();
          build(window);
          return 0;
      });

      grid.nextLine();
    }

    if (files.empty() && (clipboard.type == CLIPBOARD_TYPE_SD_FILE)) {
        files.push_back("");
    }
    for (const auto& name: files) {
      auto button = new SDmanagerButton(window, grid.getLabelSlot(), name, [this, name, window]() -> uint8_t {
          const char* const namePtr = name.c_str(); // name is captured by-value: it lives as long as the button
          auto const menu = new Menu(window);
          if (!name.empty()) {
              const char* const ext = getFileExtension(name.c_str());
              if (ext) {
                if (!strcasecmp(ext, SOUNDS_EXT)) {
                  menu->addLine(STR_PLAY_FILE, [this, namePtr]() {
                      audioQueue.stopAll();
                      audioQueue.playFile(setPathBufferToFullPath(namePtr), 0, ID_PLAY_FROM_SD_MANAGER);
                  });
                }
    #if defined(MULTIMODULE) && !defined(DISABLE_MULTI_UPDATE)
                if (!READ_ONLY() && !strcasecmp(ext, MULTI_FIRMWARE_EXT)) {
                  MultiFirmwareInformation information;
                  if (information.readMultiFirmwareInformation(namePtr) == nullptr) {
    #if defined(INTERNAL_MODULE_MULTI)
                    menu->addLine(STR_FLASH_INTERNAL_MULTI, [this, namePtr]() {
                      multiFirmwareUpdate(namePtr, INTERNAL_MODULE,
                                          MULTI_TYPE_MULTIMODULE);
                    });
    #endif
                    menu->addLine(STR_FLASH_EXTERNAL_MULTI, [this, namePtr]() {
                      multiFirmwareUpdate(namePtr, EXTERNAL_MODULE,
                                          MULTI_TYPE_MULTIMODULE);
                    });
                  }
                }
    #endif
                else if (!READ_ONLY() && !strcasecmp(ext, ELRS_FIRMWARE_EXT)) {
                  menu->addLine(STR_FLASH_EXTERNAL_ELRS, [this, namePtr]() {
                    multiFirmwareUpdate(namePtr, EXTERNAL_MODULE, MULTI_TYPE_ELRS);
                  });
                }
                // else if (isExtensionMatching(ext, BITMAPS_EXT)) {
                //   // TODO
                // }
                else if (!strcasecmp(ext, TEXT_EXT)) {
                  menu->addLine(STR_VIEW_TEXT, [this, namePtr, window]() {
                    auto textView = new ViewTextWindow(std::string{currentDir}, namePtr);
                    textView->setCloseHandler([this, window]() {
                      rebuild(window);
                    });
                  });
                }
                if (!READ_ONLY() && !strcasecmp(ext, FIRMWARE_EXT)) {
                  if (isBootloader(namePtr)) {
                    menu->addLine(STR_FLASH_BOOTLOADER, [this, namePtr]() {
                      bootloaderUpdate(namePtr);
                    });
                  }
                } else if (!READ_ONLY() && !strcasecmp(ext, SPORT_FIRMWARE_EXT)) {
                  if (HAS_SPORT_UPDATE_CONNECTOR()) {
                    menu->addLine(STR_FLASH_EXTERNAL_DEVICE, [this, namePtr]() {
                      frSkyFirmwareUpdate(namePtr, SPORT_MODULE);
                    });
                  }
                  menu->addLine(STR_FLASH_INTERNAL_MODULE, [this, namePtr]() {
                    frSkyFirmwareUpdate(namePtr, INTERNAL_MODULE);
                  });
                  menu->addLine(STR_FLASH_EXTERNAL_MODULE, [this, namePtr]() {
                    frSkyFirmwareUpdate(namePtr, EXTERNAL_MODULE);
                  });
                } else if (!READ_ONLY() && !strcasecmp(ext, FRSKY_FIRMWARE_EXT)) {
                  FrSkyFirmwareInformation information;
                  if (readFrSkyFirmwareInformation(setPathBufferToFullPath(namePtr),
                                                   information) == nullptr) {
    #if defined(INTERNAL_MODULE_PXX1) || defined(INTERNAL_MODULE_PXX2)
                    menu->addLine(STR_FLASH_INTERNAL_MODULE, [this, namePtr]() {
                      frSkyFirmwareUpdate(namePtr, INTERNAL_MODULE);
                    });
    #endif
                    if (information.productFamily ==
                        FIRMWARE_FAMILY_EXTERNAL_MODULE) {
                      menu->addLine(STR_FLASH_EXTERNAL_MODULE, [this, namePtr]() {
                        frSkyFirmwareUpdate(namePtr, EXTERNAL_MODULE);
                      });
                    }
                    if (information.productFamily == FIRMWARE_FAMILY_RECEIVER ||
                        information.productFamily == FIRMWARE_FAMILY_SENSOR) {
                      if (HAS_SPORT_UPDATE_CONNECTOR()) {
                        menu->addLine(STR_FLASH_EXTERNAL_DEVICE, [this, namePtr]() {
                          frSkyFirmwareUpdate(namePtr, SPORT_MODULE);
                        });
                      } else {
                        menu->addLine(STR_FLASH_EXTERNAL_MODULE, [this, namePtr]() {
                          frSkyFirmwareUpdate(namePtr, EXTERNAL_MODULE);
                        });
                      }
                    }
    // TODO: Integrate the remaining options
    #if 0
    #if defined(PXX2)
                    if (information.productFamily == FIRMWARE_FAMILY_RECEIVER) {
                      if (isReceiverOTAEnabledFromModule(INTERNAL_MODULE,
                                                         information.productId))
                        menu->addLine(
                            STR_FLASH_RECEIVER_BY_INTERNAL_MODULE_OTA, [=]() {
                              FrSkyFirmwareUpdate(name, INTERNAL_MODULE_OTA);
                            });
                      if (isReceiverOTAEnabledFromModule(EXTERNAL_MODULE,
                                                         information.productId))
                        menu->addLine(
                            STR_FLASH_RECEIVER_BY_EXTERNAL_MODULE_OTA, [=]() {
                              FrSkyFirmwareUpdate(name, EXTERNAL_MODULE_OTA);
                            });
                    }
                    if (information.productFamily ==
                        FIRMWARE_FAMILY_FLIGHT_CONTROLLER) {
                      menu->addLine(
                          STR_FLASH_FLIGHT_CONTROLLER_BY_INTERNAL_MODULE_OTA,
                          [=]() {
                            FrSkyFirmwareUpdate(
                                name,
                                STR_FLASH_FLIGHT_CONTROLLER_BY_INTERNAL_MODULE_OTA);
                          });
                      menu->addLine(
                          STR_FLASH_FLIGHT_CONTROLLER_BY_EXTERNAL_MODULE_OTA,
                          [=]() {
                            FrSkyFirmwareUpdate(
                                name,
                                STR_FLASH_FLIGHT_CONTROLLER_BY_INTERNAL_MODULE_OTA);
                          });
                    }
    #endif
    #if defined(BLUETOOTH)
                    if (information.productFamily ==
                        FIRMWARE_FAMILY_BLUETOOTH_CHIP) {
                      menu->addLine(STR_FLASH_BLUETOOTH_MODULE, [=]() {
                        FrSkyFirmwareUpdate(name, STR_FLASH_BLUETOOTH_MODULE);
                      });
                    }
    #endif
    #if defined(HARDWARE_POWER_MANAGEMENT_UNIT)
                    if (information.productFamily ==
                        FIRMWARE_FAMILY_POWER_MANAGEMENT_UNIT) {
                      menu->addLine(STR_FLASH_POWER_MANAGEMENT_UNIT, [=]() {
                        FrSkyFirmwareUpdate(name, STR_FLASH_POWER_MANAGEMENT_UNIT);
                      });
                    }
    #endif
    #endif
                  }
                }
    #if defined(LUA)
                else if (isExtensionMatching(ext, SCRIPTS_EXT)) {
                  std::string fullpath = std::string{currentDir} + PATH_SEPARATOR + namePtr;
                  menu->addLine(STR_EXECUTE_FILE, [this, fullpath, window]() {
                    luaExec(fullpath.c_str());
                    StandaloneLuaWindow::instance()->attach(window);
                  });
                }
    #endif
                if (strlen(namePtr) > 0) {
                    menu->addLine(STR_COPY_FILE, [this, namePtr]() {
                        clipboard.type = CLIPBOARD_TYPE_SD_FILE;
                        strncpy(clipboard.data.sd.directory, currentDir, CLIPBOARD_PATH_LEN - 1);
                        strncpy(clipboard.data.sd.filename, namePtr, CLIPBOARD_PATH_LEN - 1);
                    });
                    menu->addLine(STR_RENAME_FILE, [this, namePtr, window]() {
                        auto const few = new FileNameEditWindow(namePtr);
                        few->setCloseHandler([this, window]() {
                            rebuild(window);
                        });
                    });
                    menu->addLine(STR_DELETE_FILE, [this, namePtr, window]() {
                        f_unlink((const TCHAR*)setPathBufferToFullPath(namePtr));
                        // coord_t scrollPosition = window->getScrollPositionY();
                        window->clear();
                        build(window);
                        // window->setScrollPositionY(scrollPosition);
                    });
                }
              } // ext
          } // !name.empty()
          if (!READ_ONLY()) {
            if (clipboard.type == CLIPBOARD_TYPE_SD_FILE) {
              menu->addLine(STR_PASTE, [this, window]() {
                if (fileExists(clipboard.data.sd.filename)) {
                    pathBuffer.clear().add(FILE_COPY_PREFIX).add(clipboard.data.sd.filename);
                    sdCopyFile(clipboard.data.sd.filename, clipboard.data.sd.directory, pathBuffer, currentDir);
                }
                else {
                    sdCopyFile(clipboard.data.sd.filename, clipboard.data.sd.directory, clipboard.data.sd.filename, currentDir);
                }
                clipboard.type = CLIPBOARD_TYPE_NONE;
                rebuild(window);
              });
            }
          }
          return 0;
      }, BUTTON_BACKGROUND, COLOR_THEME_PRIMARY1);
      button->setFocusHandler([this, name, preview](bool active) {
        if (active) {
          preview->setFile(setPathBufferToFullPath(name.c_str()));
        }
      });
      grid.nextLine();
    }
  }

  window->setInnerHeight(grid.getWindowHeight());
//  preview->setHeight(max(window->height(), grid.getWindowHeight()));
}

void RadioSdManagerPage::bootloaderUpdate(const char* const name)
{
  BootloaderFirmwareUpdate bootloaderFirmwareUpdate;
  auto dialog =
      new FlashDialog<BootloaderFirmwareUpdate>(bootloaderFirmwareUpdate);
  dialog->flash(setPathBufferToFullPath(name));
}

void RadioSdManagerPage::frSkyFirmwareUpdate(const char* const name,
                                             ModuleIndex module)
{
  FrskyDeviceFirmwareUpdate deviceFirmwareUpdate(module);
  auto dialog =
      new FlashDialog<FrskyDeviceFirmwareUpdate>(deviceFirmwareUpdate);
  dialog->flash(setPathBufferToFullPath(name));
}

void RadioSdManagerPage::multiFirmwareUpdate(const char* const name,
                                             ModuleIndex module,
                                             MultiModuleType type)
{
  MultiDeviceFirmwareUpdate deviceFirmwareUpdate(module, type);
  auto dialog =
      new FlashDialog<MultiDeviceFirmwareUpdate>(deviceFirmwareUpdate);
  dialog->flash(setPathBufferToFullPath(name));
}

#if 0
bool menuRadioSdManagerInfo(event_t event)
{
  SIMPLE_SUBMENU(STR_SD_INFO_TITLE, ICON_RADIO_SD_MANAGER, 1);

  lcdDrawText(MENUS_MARGIN_LEFT, 2*FH, STR_SD_TYPE);
  lcdDrawText(100, 2*FH, SD_IS_HC() ? STR_SDHC_CARD : STR_SD_CARD);

  lcdDrawText(MENUS_MARGIN_LEFT, 3*FH, STR_SD_SIZE);
  lcdDrawNumber(100, 3*FH, sdGetSize(), LEFT, 0, nullptr, "M");

  lcdDrawText(MENUS_MARGIN_LEFT, 4*FH, STR_SD_SECTORS);
#if defined(SD_GET_FREE_BLOCKNR)
  lcdDrawNumber(100, 4*FH, SD_GET_FREE_BLOCKNR()/1000, LEFT, 0, nullptr, "/");
  lcdDrawNumber(150, 4*FH, sdGetNoSectors()/1000, LEFT);
#else
  lcdDrawNumber(100, 4*FH, sdGetNoSectors()/1000, LEFT, 0, NULL, "k");
#endif

  lcdDrawText(MENUS_MARGIN_LEFT, 5*FH, STR_SD_SPEED);
  lcdDrawNumber(100, 5*FH, SD_GET_SPEED()/1000, LEFT, 0, NULL, "kb/s");

  return true;
}
#endif

#if 0
void onSdManagerMenu(const char * result)
{
  TCHAR lfn[FF_MAX_LFN+1];

  // TODO possible buffer overflows here!

  uint8_t index = menuVerticalPosition-menuVerticalOffset;
  char *line = reusableBuffer.sdmanager.lines[index];

  if (result == STR_SD_INFO) {
    pushMenu(menuRadioSdManagerInfo);
  }
  else if (result == STR_SD_FORMAT) {
    POPUP_CONFIRMATION(STR_CONFIRM_FORMAT);
  }
  else if (result == STR_PASTE) {
    f_getcwd(lfn, FF_MAX_LFN);
    // if destination is dir, copy into that dir
    if (IS_DIRECTORY(line)) {
      strcat(lfn, PSTR("/"));
      strcat(lfn, line);
    }
    if (strcmp(clipboard.data.sd.directory, lfn)) {  // prevent copying to the same directory
      POPUP_WARNING(sdCopyFile(clipboard.data.sd.filename, clipboard.data.sd.directory, clipboard.data.sd.filename, lfn));
      REFRESH_FILES();
    }
  }
  else if (result == STR_RENAME_FILE) {
    memcpy(reusableBuffer.sdmanager.originalName, line, sizeof(reusableBuffer.sdmanager.originalName));
    uint8_t fnlen = 0, extlen = 0;
    getFileExtension(line, 0, LEN_FILE_EXTENSION_MAX, &fnlen, &extlen);
    // write spaces to allow extending the length of a filename
    memset(line + fnlen - extlen, ' ', SD_SCREEN_FILE_LENGTH - fnlen + extlen);
    line[SD_SCREEN_FILE_LENGTH-extlen] = '\0';
    s_editMode = EDIT_MODIFY_STRING;
    editNameCursorPos = 0;
  }
  else if (result == STR_ASSIGN_BITMAP) {
    memcpy(g_model.header.bitmap, line, sizeof(g_model.header.bitmap));
    storageDirty(EE_MODEL);
  }
  else if (result == STR_ASSIGN_SPLASH) {
    f_getcwd(lfn, FF_MAX_LFN);
    sdCopyFile(line, lfn, SPLASH_FILE, BITMAPS_PATH);
  }
  else if (result == STR_VIEW_TEXT) {
    getSelectionFullPath(lfn);
    pushMenuTextView(lfn);
  }
}
#endif

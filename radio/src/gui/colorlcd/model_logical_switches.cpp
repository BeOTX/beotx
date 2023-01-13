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

#include "model_logical_switches.h"
#include "opentx.h"
#include "libopenui.h"
#include "switches.h"
#include "lvgl_widgets/input_mix_line.h"

#define SET_DIRTY()     storageDirty(EE_MODEL)

static const lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(2),
                                     LV_GRID_TEMPLATE_LAST};
static const lv_coord_t col_dsc2[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1),
                                     LV_GRID_TEMPLATE_LAST};
static const lv_coord_t row_dsc[] = {LV_GRID_CONTENT,
                                     LV_GRID_TEMPLATE_LAST};

class LogicalSwitchEditPage: public Page
{
  public:
    explicit LogicalSwitchEditPage(uint8_t index):
      Page(ICON_MODEL_LOGICAL_SWITCHES),
      index(index)
    {
      buildHeader(&header);
      buildBody(&body);
    }

  protected:
    uint8_t index;
    bool active = false;
    FormGroup * logicalSwitchOneWindow = nullptr;
    StaticText * headerSwitchName = nullptr;
    NumberEdit * v2Edit = nullptr;

    bool isActive() const
    {
      return getSwitch(SWSRC_FIRST_LOGICAL_SWITCH + index);
    }

    void checkEvents() override
    {
      Page::checkEvents();
      if (active != isActive()) {
        if(isActive()) {
          lv_obj_add_state(headerSwitchName->getLvObj(), LV_STATE_USER_1);
        } else {
          lv_obj_clear_state(headerSwitchName->getLvObj(), LV_STATE_USER_1);
        }
        active = isActive();
        invalidate();
      }
    }

    void buildHeader(Window * window)
    {
      header.setTitle(STR_MENULOGICALSWITCHES);
      headerSwitchName = new StaticText(
          window,
          {PAGE_TITLE_LEFT, PAGE_TITLE_TOP + PAGE_LINE_HEIGHT,
           LCD_W - PAGE_TITLE_LEFT, PAGE_LINE_HEIGHT},
          getSwitchPositionName(SWSRC_SW1 + index), 0, COLOR_THEME_PRIMARY2);

      lv_obj_set_style_text_color(headerSwitchName->getLvObj(), makeLvColor(COLOR_THEME_ACTIVE), LV_STATE_USER_1);
      lv_obj_set_style_text_font(headerSwitchName->getLvObj(), getFont(FONT(BOLD)), LV_STATE_USER_1);
    }

    void updateLogicalSwitchOneWindow()
    {
      SwitchChoice* choice;
      NumberEdit* timer;
      
      logicalSwitchOneWindow->clear();
      logicalSwitchOneWindow->setFlexLayout();
      FlexGridLayout grid(col_dsc, row_dsc, 2);
      FlexGridLayout grid2(col_dsc2, row_dsc, 2);

      LogicalSwitchData * cs = lswAddress(index);
      uint8_t cstate = lswFamily(cs->func);

      // V1
      auto line = logicalSwitchOneWindow->newLine(&grid);
      new StaticText(line, rect_t{}, STR_V1, 0, COLOR_THEME_PRIMARY1);
      switch (cstate) {
        case LS_FAMILY_BOOL:
        case LS_FAMILY_STICKY:
        case LS_FAMILY_EDGE:
          choice = new SwitchChoice(line, rect_t{}, SWSRC_FIRST_IN_LOGICAL_SWITCHES, SWSRC_LAST_IN_LOGICAL_SWITCHES, GET_SET_DEFAULT(cs->v1));
          choice->setAvailableHandler(isSwitchAvailableInLogicalSwitches);
          break;
        case LS_FAMILY_COMP:
          new SourceChoice(line, rect_t{}, 0, MIXSRC_LAST_TELEM, GET_SET_DEFAULT(cs->v1));
          break;
        case LS_FAMILY_TIMER:
          timer = new NumberEdit(line, rect_t{}, -128, 122, GET_SET_DEFAULT(cs->v1));
          timer->setDisplayHandler([](int32_t value) {
            return formatNumberAsString(lswTimerValue(value), PREC1);
          });
          break;
        default:
          new SourceChoice(line, rect_t{}, 0, MIXSRC_LAST_TELEM, GET_DEFAULT(cs->v1),
                           [=](int32_t newValue) {
                             cs->v1 = newValue;
                             if (v2Edit != nullptr)
                             {
                               int16_t v2_min = 0, v2_max = 0;
                               getMixSrcRange(cs->v1, v2_min, v2_max);
                               v2Edit->setMin(v2_min);
                               v2Edit->setMax(v2_max);
                               v2Edit->setValue(cs->v2);
                             }
                             SET_DIRTY();
                           });
          break;
      }

      // V2
      if (cstate == LS_FAMILY_EDGE) {
        line = logicalSwitchOneWindow->newLine(&grid2);
      } else {
        line = logicalSwitchOneWindow->newLine(&grid);
      }
      new StaticText(line, rect_t{}, STR_V2, 0, COLOR_THEME_PRIMARY1);
      switch (cstate) {
        case LS_FAMILY_BOOL:
        case LS_FAMILY_STICKY:
          choice = new SwitchChoice(line, rect_t{}, SWSRC_FIRST_IN_LOGICAL_SWITCHES, SWSRC_LAST_IN_LOGICAL_SWITCHES, GET_SET_DEFAULT(cs->v2));
          choice->setAvailableHandler(isSwitchAvailableInLogicalSwitches);
          break;
        case LS_FAMILY_EDGE:
          {
            auto edit1 = new NumberEdit(line, rect_t{}, -129, 122, GET_DEFAULT(cs->v2));
            auto edit2 = new NumberEdit(line, rect_t{}, -1, 222 - cs->v2, GET_SET_DEFAULT(cs->v3));
            edit1->setSetValueHandler([=](int32_t newValue) {
              cs->v2 = newValue;
              SET_DIRTY();
              edit2->setMax(222 - cs->v2);
              edit2->setValue(cs->v3);
            });
            edit1->setDisplayHandler([](int32_t value) {
              return formatNumberAsString(lswTimerValue(value), PREC1);
            });
            edit2->setDisplayHandler([cs](int32_t value) {
              if (value < 0)
                return std::string("<<");
              else if (value == 0)
                return std::string("--");
              else {
                return formatNumberAsString(lswTimerValue(cs->v2 + value), PREC1);
              }
            });
          }
          break;
        case LS_FAMILY_COMP:
          new SourceChoice(line, rect_t{}, 0, MIXSRC_LAST_TELEM, GET_SET_DEFAULT(cs->v2));
          break;
        case LS_FAMILY_TIMER:
          timer = new NumberEdit(line, rect_t{}, -128, 122, GET_SET_DEFAULT(cs->v2));
          timer->setDisplayHandler([](int32_t value) {
            return formatNumberAsString(lswTimerValue(value), PREC1);
          });
          break;
        default:
          int16_t v2_min = 0, v2_max = 0;
          getMixSrcRange(cs->v1, v2_min, v2_max);
          v2Edit = new NumberEdit(line, rect_t{},
                                  v2_min, v2_max, GET_SET_DEFAULT(cs->v2));

          v2Edit->setDisplayHandler([=](int value) -> std::string {
            if (cs->v1 <= MIXSRC_LAST_CH) value = calc100toRESX(value);
            std::string txt = getSourceCustomValueString(cs->v1, value, 0);
            return txt;
          });
          break;
      }

      // AND switch
      line = logicalSwitchOneWindow->newLine(&grid);
      new StaticText(line, rect_t{}, STR_AND_SWITCH, 0, COLOR_THEME_PRIMARY1);
      choice = new SwitchChoice(line, rect_t{}, -MAX_LS_ANDSW, MAX_LS_ANDSW, GET_SET_DEFAULT(cs->andsw));
      choice->setAvailableHandler(isSwitchAvailableInLogicalSwitches);

      // Duration
      line = logicalSwitchOneWindow->newLine(&grid);
      new StaticText(line, rect_t{}, STR_DURATION, 0, COLOR_THEME_PRIMARY1);
      auto edit = new NumberEdit(line, rect_t{}, 0, MAX_LS_DURATION, GET_SET_DEFAULT(cs->duration), 0, PREC1);
      edit->setZeroText("---");

      // Delay
      line = logicalSwitchOneWindow->newLine(&grid);
      new StaticText(line, rect_t{}, STR_DELAY, 0, COLOR_THEME_PRIMARY1);
      if (cstate == LS_FAMILY_EDGE) {
        new StaticText(line, rect_t{}, STR_NA, 0, COLOR_THEME_PRIMARY1);
      }
      else {
        auto edit = new NumberEdit(line, rect_t{}, 0, MAX_LS_DELAY, GET_SET_DEFAULT(cs->delay), 0, PREC1);
        edit->setZeroText("---");
      }
    }

    void buildBody(FormWindow * window)
    {
      window->setFlexLayout();
      FlexGridLayout grid(col_dsc, row_dsc, 2);
      lv_obj_set_style_pad_all(window->getLvObj(), lv_dpx(8), 0);

      LogicalSwitchData * cs = lswAddress(index);

      // LS Func
      auto line = window->newLine(&grid);
      new StaticText(line, rect_t{}, STR_FUNC, 0, COLOR_THEME_PRIMARY1);
      auto functionChoice = new Choice(line, rect_t{}, STR_VCSWFUNC, 0, LS_FUNC_MAX, GET_DEFAULT(cs->func));
      functionChoice->setSetValueHandler([=](int32_t newValue) {
          cs->func = newValue;
          if (lswFamily(cs->func) == LS_FAMILY_TIMER) {
            cs->v1 = cs->v2 = 0;
          }
          else if (lswFamily(cs->func) == LS_FAMILY_EDGE) {
            cs->v1 = 0;
            cs->v2 = -129;
            cs->v3 = 0;
          }
          else {
            cs->v1 = cs->v2 = 0;
          }
          SET_DIRTY();
          updateLogicalSwitchOneWindow();
      });
      functionChoice->setAvailableHandler(isLogicalSwitchFunctionAvailable);

      logicalSwitchOneWindow = new FormWindow(window, rect_t{});
      updateLogicalSwitchOneWindow();
    }
};

void getsEdgeDelayParam(char* s, LogicalSwitchData * ls)
{
  strcpy(s, "[");
  BitmapBuffer::formatNumberAsString(s+1, 6, lswTimerValue(ls->v2), PREC1);
  strcat(s, ":");
  if (ls->v3 < 0)
    strcat(s, "<<");
  else if (ls->v3 == 0)
    strcat(s, "--");
  else
    BitmapBuffer::formatNumberAsString(s+strlen(s), 6, lswTimerValue(ls->v2+ls->v3), PREC1);
  strcat(s, "]");
}

void putsEdgeDelayParam(BitmapBuffer * dc, coord_t x, coord_t y, LogicalSwitchData * ls, LcdFlags flags = 0)
{
  char s[20];
  getsEdgeDelayParam(s, ls);
  dc->drawText(x, y, s, flags);
}

#if LCD_W > LCD_H // Landscape

#define TXT_ALIGN   LV_GRID_ALIGN_CENTER

static const lv_coord_t b_col_dsc[] = {
  43, 49, 88, 93, 87, 34, 34,
  LV_GRID_TEMPLATE_LAST
};

static const lv_coord_t b_row_dsc[] = {LV_GRID_CONTENT,
                                     LV_GRID_TEMPLATE_LAST};
#else // Portrait

#define TXT_ALIGN   LV_GRID_ALIGN_START

static const lv_coord_t b_col_dsc[] = {
  43, LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1),
  LV_GRID_TEMPLATE_LAST
};

static const lv_coord_t b_row_dsc[] = {LV_GRID_CONTENT,
                                     LV_GRID_CONTENT,
                                     LV_GRID_TEMPLATE_LAST};
#endif

class LogicalSwitchButton : public Button
{
 public:
  LogicalSwitchButton(Window* parent, const rect_t& rect, int lsIndex) :
      Button(parent, rect, nullptr, 0, 0, input_mix_line_create), lsIndex(lsIndex)
  {
#if LCD_H > LCD_W
    padTop(0);
#endif
    padLeft(4);
    lv_obj_set_layout(lvobj, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(lvobj, b_col_dsc, b_row_dsc);
    lv_obj_set_style_pad_row(lvobj, 0, 0);
    lv_obj_set_style_pad_column(lvobj, 4, 0);

    check(isActive());

    lv_obj_update_layout(parent->getLvObj());
    if(lv_obj_is_visible(lvobj)) delayed_init(nullptr);

    lv_obj_add_event_cb(lvobj, LogicalSwitchButton::on_draw, LV_EVENT_DRAW_MAIN_BEGIN, nullptr);
  }

  static void on_draw(lv_event_t * e)
  {
    lv_obj_t* target = lv_event_get_target(e);
    auto line = (LogicalSwitchButton*)lv_obj_get_user_data(target);
    if (line) {
      if (!line->init)
        line->delayed_init(e);
      else
        line->refresh();
    }
  }
  
  void delayed_init(lv_event_t* e)
  {
    uint8_t col = 0, row = 0;

    LogicalSwitchData* ls = lswAddress(lsIndex);
    uint8_t lsFamily = lswFamily(ls->func);

    lsName = lv_label_create(lvobj);
    lv_obj_set_style_text_align(lsName, LV_TEXT_ALIGN_LEFT, 0);
#if LCD_W > LCD_H
    lv_obj_set_grid_cell(lsName, LV_GRID_ALIGN_START, col++, 1, LV_GRID_ALIGN_CENTER, row, 1);
#else
    lv_obj_set_grid_cell(lsName, LV_GRID_ALIGN_START, col++, 1, LV_GRID_ALIGN_CENTER, row, 2);
#endif

    lsFunc = lv_label_create(lvobj);
    lv_obj_set_style_text_align(lsFunc, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_grid_cell(lsFunc, LV_GRID_ALIGN_START, col++, 1, LV_GRID_ALIGN_CENTER, row, 1);

    lsV1 = lv_label_create(lvobj);
    lv_obj_set_style_text_align(lsV1, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_grid_cell(lsV1, TXT_ALIGN, col++, 1, LV_GRID_ALIGN_CENTER, row, 1);

    lsV2 = lv_label_create(lvobj);
    lv_obj_set_style_text_align(lsV2, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_grid_cell(lsV2, TXT_ALIGN, col++, 1, LV_GRID_ALIGN_CENTER, row, 1);

#if LCD_H > LCD_W
    col = 1;
    row = 1;
#endif

    lsAnd = lv_label_create(lvobj);
    lv_obj_set_style_text_align(lsAnd, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_grid_cell(lsAnd, TXT_ALIGN, col++, 1, LV_GRID_ALIGN_CENTER, row, 1);

    lsDuration = lv_label_create(lvobj);
    lv_obj_set_style_text_align(lsDuration, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_grid_cell(lsDuration, TXT_ALIGN, col++, 1, LV_GRID_ALIGN_CENTER, row, 1);

    lsDelay = lv_label_create(lvobj);
    lv_obj_set_style_text_align(lsDelay, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_grid_cell(lsDelay, TXT_ALIGN, col++, 1, LV_GRID_ALIGN_CENTER, row, 1);

    init = true;
    refresh();
    lv_obj_update_layout(lvobj);

    if(e) {
      auto param = lv_event_get_param(e);
      lv_event_send(lvobj, LV_EVENT_DRAW_MAIN, param);
    }
  }

  bool isActive() const
  {
    return getSwitch(SWSRC_FIRST_LOGICAL_SWITCH + lsIndex);
  }

  void checkEvents() override
  {
    Button::checkEvents();
    check(isActive());
  }

  void refresh()
  {
    if (!init) return;
    
    char s[20];

    LogicalSwitchData* ls = lswAddress(lsIndex);
    uint8_t lsFamily = lswFamily(ls->func);

    lv_label_set_text(lsName, getSwitchPositionName(SWSRC_SW1 + lsIndex));
    lv_label_set_text(lsFunc, STR_VCSWFUNC[ls->func]);

    // CSW params - V1
    switch (lsFamily) {
      case LS_FAMILY_BOOL:
      case LS_FAMILY_STICKY:
      case LS_FAMILY_EDGE:
        lv_label_set_text(lsV1, getSwitchPositionName(ls->v1));
        break;
      case LS_FAMILY_TIMER:
        BitmapBuffer::formatNumberAsString(s, 6, lswTimerValue(ls->v1), PREC1);
        lv_label_set_text(lsV1, s);
        break;
      case LS_FAMILY_COMP:
      default:
        lv_label_set_text(lsV1, getSourceString(ls->v1));
        break;
    }

    // CSW params - V2
    switch (lsFamily) {
      case LS_FAMILY_BOOL:
      case LS_FAMILY_STICKY:
        lv_label_set_text(lsV2, getSwitchPositionName(ls->v2));
        break;
      case LS_FAMILY_EDGE:
        getsEdgeDelayParam(s, ls);
        lv_label_set_text(lsV2, s);
        break;
      case LS_FAMILY_TIMER:
        BitmapBuffer::formatNumberAsString(s, 6, lswTimerValue(ls->v2), PREC1);
        lv_label_set_text(lsV2, s);
        break;
      case LS_FAMILY_COMP:
        lv_label_set_text(lsV2, getSourceString(ls->v2));
        break;
      default:
        lv_label_set_text(lsV2, getSourceCustomValueString(ls->v1, (ls->v1 <= MIXSRC_LAST_CH ? calc100toRESX(ls->v2) : ls->v2), 0));
        break;
    }

    // AND switch
    lv_label_set_text(lsAnd, getSwitchPositionName(ls->andsw));

    // CSW duration
    if (ls->duration > 0) {
      BitmapBuffer::formatNumberAsString(s, 6, ls->duration, PREC1);
    } else {
      s[0] = 0;
    }
    lv_label_set_text(lsDuration, s);

    // CSW delay
    if (lsFamily != LS_FAMILY_EDGE && ls->delay > 0) {
      BitmapBuffer::formatNumberAsString(s, 6, ls->delay, PREC1);
    } else {
      s[0] = 0;
    }
    lv_label_set_text(lsDelay, s);
  }

 protected:
  bool init = false;
  uint8_t lsIndex;

  lv_obj_t* lsName = nullptr;
  lv_obj_t* lsFunc = nullptr;
  lv_obj_t* lsV1 = nullptr;
  lv_obj_t* lsV2 = nullptr;
  lv_obj_t* lsAnd = nullptr;
  lv_obj_t* lsDuration = nullptr;
  lv_obj_t* lsDelay = nullptr;
};

#if LCD_W > LCD_H
#define LS_BUTTON_H 34
#else
#define LS_BUTTON_H 45
#endif

ModelLogicalSwitchesPage::ModelLogicalSwitchesPage():
  PageTab(STR_MENULOGICALSWITCHES, ICON_MODEL_LOGICAL_SWITCHES)
{
}

void ModelLogicalSwitchesPage::rebuild(FormWindow * window)
{
  // When window.clear() is called the last button on screen is given focus (???)
  // This causes the page to jump to the end when rebuilt.
  // Set flag to bypass the button focus handler and reset focusIndex when rebuilding
  isRebuilding = true;
  window->clear();
  build(window);
  isRebuilding = false;
}

void ModelLogicalSwitchesPage::build(FormWindow* window)
{
#if LCD_W > LCD_H
  #define PER_ROW 6
  static const lv_coord_t l_col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1),
                                         LV_GRID_TEMPLATE_LAST};
#else
  #define PER_ROW 4
  static const lv_coord_t l_col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1),
                                         LV_GRID_TEMPLATE_LAST};
#endif

  window->padAll(4);

  auto form = new FormWindow(window, rect_t{});
  form->setFlexLayout();
  form->padAll(0);

  FlexGridLayout grid(l_col_dsc, row_dsc, 2);

  FormWindow::Line* line;
  firstActiveButton = nullptr;
  firstInactiveButton = nullptr;
  bool hasFocusButton = false;
  Button* button;

  // Reset focusIndex after switching tabs
  if (!isRebuilding)
    focusIndex = prevFocusIndex;

  uint8_t scol = 0;

  for (uint8_t i = 0; i < MAX_LOGICAL_SWITCHES; i++) {
    LogicalSwitchData* ls = lswAddress(i);

    bool isActive = (ls->func != LS_FUNC_NONE);

    if (!isActive) {
      if (scol == 0) {
        line = form->newLine(&grid);
        lv_obj_set_style_pad_column(line->getLvObj(), 4, LV_PART_MAIN);
      }

      button = new TextButton(line, rect_t{0, 0, 0, LS_BUTTON_H}, getSwitchPositionName(SWSRC_SW1 + i));

      if (firstInactiveButton == nullptr)
        firstInactiveButton = button;

      button->setLongPressHandler([=]() -> uint8_t {
        if (firstActiveButton)
          lv_group_focus_obj(firstActiveButton->getLvObj());
        return 0;
      });

      lv_obj_set_grid_cell(button->getLvObj(), LV_GRID_ALIGN_STRETCH, scol, 1, LV_GRID_ALIGN_CENTER, 0, 1);
      scol = (scol + 1) % PER_ROW;
    } else {
      line = form->newLine(&grid);
      scol = 0;

      button = new LogicalSwitchButton(line, rect_t{0, 0, window->width() - 12, LS_BUTTON_H}, i);

      if (firstActiveButton == nullptr)
        firstActiveButton = button;

      button->setLongPressHandler([=]() -> uint8_t {
        if (firstInactiveButton)
          lv_group_focus_obj(firstInactiveButton->getLvObj());
        return 0;
      });

      lv_obj_set_grid_cell(button->getLvObj(), LV_GRID_ALIGN_CENTER, 0, PER_ROW, LV_GRID_ALIGN_CENTER, 0, 1);
    }

    button->setPressHandler([=]() {
      Menu* menu = new Menu(window);
      menu->addLine(STR_EDIT, [=]() {
        Window * lsWindow = new LogicalSwitchEditPage(i);
        lsWindow->setCloseHandler([=]() {
          if (isActive)
            lv_event_send(button->getLvObj(), LV_EVENT_VALUE_CHANGED, nullptr);
          else
            rebuild(window);
        });
      });
      if (isActive) {
        menu->addLine(STR_COPY, [=]() {
          clipboard.type = CLIPBOARD_TYPE_CUSTOM_SWITCH;
          clipboard.data.csw = *ls;
        });
      }
      if (clipboard.type == CLIPBOARD_TYPE_CUSTOM_SWITCH)
        menu->addLine(STR_PASTE, [=]() {
          *ls = clipboard.data.csw;
          storageDirty(EE_MODEL);
          rebuild(window);
        });
      if (isActive || ls->v1 || ls->v2 || ls->delay || ls->duration || ls->andsw) {
        menu->addLine(STR_CLEAR, [=]() {
          memset(ls, 0, sizeof(LogicalSwitchData));
          storageDirty(EE_MODEL);
          rebuild(window);
        });
      }
      return 0;
    });

    if (focusIndex == i) {
      hasFocusButton = true;
      lv_group_focus_obj(button->getLvObj());
    }

    button->setFocusHandler([=](bool hasFocus) {
      if (hasFocus && !isRebuilding) {
        prevFocusIndex = focusIndex;
        focusIndex = i;
      }
    });
  }

  if (!hasFocusButton)
  {
    if (firstActiveButton)
      lv_group_focus_obj(firstActiveButton->getLvObj());
    else if (firstInactiveButton)
      lv_group_focus_obj(firstInactiveButton->getLvObj());
  }
}

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

#include "opentx.h"
#include "model_gvars.h"
#include "libopenui.h"
#include "numberedit.h"
#include "lvgl_widgets/input_mix_line.h"

#define SET_DIRTY() storageDirty(EE_MODEL)

#define TEXT_LEFT_MARGIN 2
#define GVAR_NAME_SIZE 44
#if LCD_W > LCD_H
#define GVAR_VAL_SIZE 45
#else
#define GVAR_VAL_SIZE 50
#endif

class GVarStyle
{
  public:
    GVarStyle() {}

    void init()
    {
      if(!styleInitDone)
      {
        styleInitDone=true;

        lv_style_init(&fmContStyle);
        lv_style_set_pad_all(&fmContStyle, 0);
        lv_style_set_width(&fmContStyle, GVAR_VAL_SIZE);
        lv_style_set_height(&fmContStyle, PAGE_LINE_HEIGHT * 2 - 6);
        lv_style_set_flex_flow(&fmContStyle, LV_FLEX_FLOW_COLUMN);
        lv_style_set_layout(&fmContStyle, LV_LAYOUT_FLEX);
        lv_style_set_bg_color(&fmContStyle, makeLvColor(COLOR_THEME_PRIMARY2));
        lv_style_set_bg_opa(&fmContStyle, LV_OPA_COVER);

        lv_style_init(&fmContStyleChecked);
        lv_style_set_bg_color(&fmContStyleChecked, makeLvColor(COLOR_THEME_SECONDARY3));

        lv_style_init(&fmLabelStyle);
        lv_style_set_height(&fmLabelStyle, PAGE_LINE_HEIGHT - 6);
        lv_style_set_width(&fmLabelStyle, GVAR_VAL_SIZE);
        lv_style_set_text_font(&fmLabelStyle, getFont(FONT(XS)));
        lv_style_set_text_color(&fmLabelStyle, makeLvColor(COLOR_THEME_SECONDARY1));
        lv_style_set_text_align(&fmLabelStyle, LV_TEXT_ALIGN_CENTER);

        lv_style_init(&fmValueStyle);
        lv_style_set_height(&fmValueStyle, PAGE_LINE_HEIGHT);
        lv_style_set_width(&fmValueStyle, GVAR_VAL_SIZE);
        lv_style_set_text_font(&fmValueStyle, getFont(FONT(STD)));
        lv_style_set_text_color(&fmValueStyle, makeLvColor(COLOR_THEME_SECONDARY1));
        lv_style_set_text_align(&fmValueStyle, LV_TEXT_ALIGN_CENTER);

        lv_style_init(&fmValueStyleSmall);
        lv_style_set_text_font(&fmValueStyleSmall, getFont(FONT(XS)));
        lv_style_set_pad_top(&fmValueStyleSmall, 3);

        lv_style_init(&fmNameStyle);
        lv_style_set_width(&fmNameStyle, GVAR_NAME_SIZE);
        lv_style_set_text_font(&fmNameStyle, getFont(FONT(STD)));
        lv_style_set_text_color(&fmNameStyle, makeLvColor(COLOR_THEME_SECONDARY1));
        lv_style_set_text_align(&fmNameStyle, LV_TEXT_ALIGN_LEFT);
        lv_style_set_pad_left(&fmNameStyle, 2);
      }
    }

    void setContStyle(lv_obj_t* obj)
    {
      init();
      lv_obj_add_style(obj, &fmContStyle, LV_PART_MAIN);
      lv_obj_add_style(obj, &fmContStyleChecked, LV_PART_MAIN|LV_STATE_CHECKED);
    }

    void setLabelStyle(lv_obj_t* obj)
    {
      init();
      lv_obj_add_style(obj, &fmLabelStyle, LV_PART_MAIN);
    }

    void setValueStyle(lv_obj_t* obj)
    {
      init();
      lv_obj_add_style(obj, &fmValueStyle, LV_PART_MAIN);
      lv_obj_add_style(obj, &fmValueStyleSmall, LV_PART_MAIN|LV_STATE_USER_1);
    }

    void setNameStyle(lv_obj_t* obj)
    {
      init();
      lv_obj_add_style(obj, &fmNameStyle, LV_PART_MAIN);
    }

  private:
    lv_style_t fmNameStyle;
    lv_style_t fmContStyle;
    lv_style_t fmContStyleChecked;
    lv_style_t fmLabelStyle;
    lv_style_t fmValueStyle;
    lv_style_t fmValueStyleSmall;
    bool styleInitDone;
};

static GVarStyle gvarStyle;

class GVarButton : public Button
{
 public:
  GVarButton(FormGroup* parent, const rect_t& rect, uint8_t gvar) :
      Button(parent, rect, nullptr, 0, 0, input_mix_line_create), gvarIdx(gvar)
  {
    setHeight(LV_SIZE_CONTENT);
    setWidth(LV_PCT(100));

    build();
  }

 protected:
  void checkEvents()
  {
    Button::checkEvents();
    uint8_t newFM = getFlightMode();
    if (currentFlightMode != newFM) {
      lv_obj_add_state(fmCont[newFM], LV_STATE_CHECKED);
      lv_obj_clear_state(fmCont[currentFlightMode], LV_STATE_CHECKED);

      currentFlightMode = newFM;
    }
    for (int flightMode = 0; flightMode < MAX_FLIGHT_MODES; flightMode++) {
      FlightModeData* fmData = &g_model.flightModeData[flightMode];
      if (values[flightMode] != fmData->gvars[gvarIdx]) {
        updateValueText(flightMode);
      }
    }
  }

 protected:
  uint8_t gvarIdx;
  int lines;
  int32_t gvarSum = 0;            // used for invalidation
  uint8_t currentFlightMode = 0;  // used for invalidation
  lv_obj_t* fmCont[MAX_FLIGHT_MODES];
  lv_obj_t* valueTexts[MAX_FLIGHT_MODES];
  gvar_t values[MAX_FLIGHT_MODES];

  void build()
  {
    currentFlightMode = getFlightMode();

    lv_obj_enable_style_refresh(false);

    lv_obj_set_flex_flow(lvobj, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_all(lvobj, 0, LV_PART_MAIN);
    lv_obj_set_flex_align(lvobj, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_AROUND);

    auto lbl = lv_label_create(lvobj);
    gvarStyle.setNameStyle(lbl);
    lv_label_set_text(lbl, getGVarString(gvarIdx));

    lv_obj_t* container = lv_obj_create(lvobj);
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_style_flex_grow(container, 2, LV_PART_MAIN);
    lv_obj_set_style_pad_all(container, 0, LV_PART_MAIN);
    lv_obj_set_height(container, LV_SIZE_CONTENT);
    lv_obj_add_flag(container, LV_OBJ_FLAG_EVENT_BUBBLE);

    for (int flightMode = 0; flightMode < MAX_FLIGHT_MODES; flightMode++) {
      fmCont[flightMode] = lv_obj_create(container);
      gvarStyle.setContStyle(fmCont[flightMode]);
      lv_obj_set_user_data(fmCont[flightMode], this);
      lv_obj_add_flag(fmCont[flightMode], LV_OBJ_FLAG_EVENT_BUBBLE);
      if (flightMode == currentFlightMode) {
        lv_obj_add_state(fmCont[flightMode], LV_STATE_CHECKED);
      }

      char label[16] = {};
      getFlightModeString(label, flightMode + 1);

      lbl = lv_label_create(fmCont[flightMode]);
      gvarStyle.setLabelStyle(lbl);
      lv_label_set_text(lbl, label);

      valueTexts[flightMode] = lv_label_create(fmCont[flightMode]);
      gvarStyle.setValueStyle(valueTexts[flightMode]);

      updateValueText(flightMode);
    }

    lv_obj_enable_style_refresh(true);
  }

  void updateValueText(uint8_t flightMode)
  {
    lv_obj_t* field = valueTexts[flightMode];
    gvar_t value = g_model.flightModeData[flightMode].gvars[gvarIdx];
    values[flightMode] = value;

    if (value > GVAR_MAX) {
      uint8_t fm = value - GVAR_MAX - 1;
      if (fm >= flightMode) fm += 1;
      char label[16] = {};
      getFlightModeString(label, fm + 1);

      lv_label_set_text(field, label);
    } else {
      uint8_t unit = g_model.gvars[gvarIdx].unit;
      const char* suffix = (unit == 1) ? "%" : "";
      uint8_t prec = g_model.gvars[gvarIdx].prec;
      if (prec)
        lv_label_set_text_fmt(field, "%d.%01u%s", value / 10,
                              (value < 0) ? (-value) % 10 : value % 10, suffix);
      else
        lv_label_set_text_fmt(field, "%d%s", value, suffix);
      if (unit) {
        if (value <= -1000 || value >= 1000 || (prec && (value <= -100))) {
          lv_obj_add_state(field, LV_STATE_USER_1);
        } else {
          lv_obj_clear_state(field, LV_STATE_USER_1);
        }
      }
    }
  }
};

class GVarEditWindow : public Page
{
 public:
  explicit GVarEditWindow(uint8_t gvarIndex) :
      Page(ICON_MODEL_GVARS), index(gvarIndex)
  {
    buildHeader(&header);
    buildBody(&body);
  }

 protected:
  uint8_t index;
  gvar_t lastGVar = 0;
  uint8_t lastFlightMode = 255; // Force initial setting of header title
  NumberEdit* min = nullptr;
  NumberEdit* max = nullptr;
  NumberEdit* values[MAX_FLIGHT_MODES] = {};
  StaticText* gVarInHeader = nullptr;

  void buildHeader(Window* window)
  {
    header.setTitle(STR_MENU_GLOBAL_VARS);
    gVarInHeader = header.setTitle2("");
  }

  void checkEvents()
  {
    Page::checkEvents();
    if (gVarInHeader &&
        ((lastFlightMode != getFlightMode()) ||
         (lastGVar != g_model.flightModeData[getFlightMode()].gvars[index]))) {
      char label[32];
      lastFlightMode = getFlightMode();
      FlightModeData* fmData = &g_model.flightModeData[lastFlightMode];
      lastGVar = fmData->gvars[index];
      sprintf(label, "%s%d=", STR_GV, index + 1);
      if (lastGVar > GVAR_MAX) {
        uint8_t fm = lastGVar - GVAR_MAX - 1;
        if (fm >= lastFlightMode) fm++;
        getFlightModeString(label + strlen(label), fm + 1);
      } else {
        strcat(label, getGVarValue(index, lastGVar, 0).c_str());
      }
      gVarInHeader->setText(label);
      for (auto& value : values) {
        value->invalidate();
      }
    }
  }

  void setProperties(int onlyForFlightMode = -1)
  {
    GVarData* gvar = &g_model.gvars[index];
    int32_t minValue = GVAR_MIN + gvar->min;
    int32_t maxValue = GVAR_MAX - gvar->max;
    const char* suffix = gvar->unit ? "%" : "";

    LcdFlags prec = gvar->prec ? PREC1 : 0;
    if (min && max) {
      min->setMax(maxValue);
      max->setMin(minValue);

      min->setSuffix(suffix);
      max->setSuffix(suffix);

      LcdFlags minFlags = min->getTextFlags();
      LcdFlags maxFlags = max->getTextFlags();
      if (gvar->prec) {
        minFlags |= PREC1;
        maxFlags |= PREC1;
      } else {
        minFlags &= ~PREC1;
        maxFlags &= ~PREC1;
      }
      min->setTextFlags(minFlags);
      max->setTextFlags(maxFlags);

      min->update();
      max->update();
    }
    FlightModeData* fmData;
    for (int fm = 0; fm < MAX_FLIGHT_MODES; fm++) {
      if (values[fm] == nullptr)  // KLK: the order of calls has changed and
                                  // this might not be initialized yet.
        continue;

      if (onlyForFlightMode >= 0 && fm != onlyForFlightMode) continue;
      fmData = &g_model.flightModeData[fm];

      // custom value
      if (fmData->gvars[index] <= GVAR_MAX || fm == 0) {
        values[fm]->setMin(GVAR_MIN + gvar->min);
        values[fm]->setMax(GVAR_MAX - gvar->max);

        LcdFlags flags = values[fm]->getTextFlags();
        if (gvar->prec)
          flags |= PREC1;
        else
          flags &= ~PREC1;
        values[fm]->setTextFlags(flags);

        values[fm]->setDisplayHandler(nullptr);
      } else {
        values[fm]->setMin(GVAR_MAX + 1);
        values[fm]->setMax(GVAR_MAX + MAX_FLIGHT_MODES - 1);
        values[fm]->setDisplayHandler([=](int32_t value) {
          uint8_t targetFlightMode = value - GVAR_MAX - 1;
          if (targetFlightMode >= fm) targetFlightMode++;
          char label[16];
          getFlightModeString(label, targetFlightMode + 1);
          return std::string(label);
        });
      }

      values[fm]->setSuffix(suffix);
      values[fm]->invalidate();
    }
    if (gVarInHeader) gVarInHeader->invalidate();
  }

  void buildBody(FormWindow* window)
  {
    static const lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1),
                                         LV_GRID_FR(2), LV_GRID_TEMPLATE_LAST};
    static const lv_coord_t row_dsc[] = {LV_GRID_CONTENT, LV_GRID_CONTENT,
                                         LV_GRID_TEMPLATE_LAST};

    window->setFlexLayout();
    window->padAll(4);
    FlexGridLayout grid(col_dsc, row_dsc, 2);
    auto line = window->newLine(&grid);

    GVarData* gvar = &g_model.gvars[index];

    new StaticText(line, rect_t{}, STR_NAME, 0, COLOR_THEME_PRIMARY1);
    grid.nextCell();
    Window* input =
        new ModelTextEdit(line, rect_t{}, gvar->name, LEN_GVAR_NAME);
    lv_obj_set_style_grid_cell_x_align(input->getLvObj(), LV_GRID_ALIGN_STRETCH,
                                       0);

    line = window->newLine(&grid);

    new StaticText(line, rect_t{}, STR_UNIT, 0, COLOR_THEME_PRIMARY1);
    grid.nextCell();
    input = new Choice(line, rect_t{}, "\001-%", 0, 1, GET_DEFAULT(gvar->unit),
                       [=](int16_t newValue) {
                         gvar->unit = newValue;
                         SET_DIRTY();
                         setProperties();
                       });
    lv_obj_set_style_grid_cell_x_align(input->getLvObj(), LV_GRID_ALIGN_STRETCH,
                                       0);

    line = window->newLine(&grid);

    new StaticText(line, rect_t{}, STR_PRECISION, 0, COLOR_THEME_PRIMARY1);
    grid.nextCell();
    input = new Choice(line, rect_t{}, STR_VPREC, 0, 1, GET_DEFAULT(gvar->prec),
                       [=](int16_t newValue) {
                         gvar->prec = newValue;
                         SET_DIRTY();
                         setProperties();
                       });
    lv_obj_set_style_grid_cell_x_align(input->getLvObj(), LV_GRID_ALIGN_STRETCH,
                                       0);

    line = window->newLine(&grid);

    new StaticText(line, rect_t{}, STR_MIN, 0, COLOR_THEME_PRIMARY1);
    grid.nextCell();
    min = new NumberEdit(
        line, rect_t{}, GVAR_MIN, GVAR_MAX - gvar->max,
        [=] { return gvar->min + GVAR_MIN; },
        [=](int32_t newValue) {
          gvar->min = newValue - GVAR_MIN;
          SET_DIRTY();
          setProperties();
        });
    min->setAccelFactor(16);
    lv_obj_set_style_grid_cell_x_align(min->getLvObj(), LV_GRID_ALIGN_STRETCH,
                                       0);

    line = window->newLine(&grid);

    new StaticText(line, rect_t{}, STR_MAX, 0, COLOR_THEME_PRIMARY1);
    grid.nextCell();
    max = new NumberEdit(
        line, rect_t{}, GVAR_MIN + gvar->min, GVAR_MAX,
        [=] { return GVAR_MAX - gvar->max; },
        [=](int32_t newValue) {
          gvar->max = GVAR_MAX - newValue;
          SET_DIRTY();
          setProperties();
        });
    max->setAccelFactor(16);
    lv_obj_set_style_grid_cell_x_align(max->getLvObj(), LV_GRID_ALIGN_STRETCH,
                                       0);

    line = window->newLine(&grid);
    char flightModeName[16];
    FlightModeData* fmData;

    for (int flightMode = 0; flightMode < MAX_FLIGHT_MODES; flightMode++) {
      fmData = &g_model.flightModeData[flightMode];
      getFlightModeString(flightModeName, flightMode + 1);

      int userNameLen = zlen(fmData->name, LEN_FLIGHT_MODE_NAME);

      if (userNameLen > 0) {
        strcpy(flightModeName, fmData->name);
      }
      new StaticText(line, rect_t{}, flightModeName, 0, COLOR_THEME_PRIMARY1);
      if (flightMode > 0) {
        auto cb = new CheckBox(
            line, rect_t{}, [=] { return fmData->gvars[index] <= GVAR_MAX; },
            [=](uint8_t checked) {
              fmData->gvars[index] = checked ? 0 : GVAR_MAX + 1;
              setProperties(flightMode);
            });
        lv_obj_set_style_grid_cell_x_align(cb->getLvObj(), LV_GRID_ALIGN_END,
                                           0);
        lv_obj_invalidate(cb->getLvObj());
        cb->setLabel(STR_OWN);

      } else {
        grid.nextCell();
      }

      values[flightMode] = new NumberEdit(
          line, rect_t{}, GVAR_MIN + gvar->min, GVAR_MAX + MAX_FLIGHT_MODES - 1,
          GET_SET_DEFAULT(fmData->gvars[index]));
      values[flightMode]->setAccelFactor(16);
      line = window->newLine(&grid);
    }

    setProperties();
    lv_obj_set_height(window->getLvObj(),
                      LCD_H - lv_obj_get_height(header.getLvObj()));
    lv_obj_set_height(lvobj, LCD_H);
  }
};

void ModelGVarsPage::rebuild(FormWindow* window)
{
  auto scroll_y = lv_obj_get_scroll_y(window->getLvObj());
  window->clear();
  build(window);
  lv_obj_scroll_to_y(window->getLvObj(), scroll_y, LV_ANIM_OFF);
}

void ModelGVarsPage::build(FormWindow* window)
{
  window->setFlexLayout(LV_FLEX_FLOW_COLUMN, 2);

  for (uint8_t index = 0; index < MAX_GVARS; index++) {
    Button* button = new GVarButton(window, rect_t{}, index);
    button->setPressHandler([=]() {
      Menu* menu = new Menu(window);
      menu->addLine(STR_EDIT, [=]() {
        Window* editWindow = new GVarEditWindow(index);
        editWindow->setCloseHandler([=]() { rebuild(window); });
      });
      menu->addLine(STR_CLEAR, [=]() {
        for (auto& flightMode : g_model.flightModeData) {
          flightMode.gvars[index] = 0;
        }
        storageDirty(EE_MODEL);
      });
      return 0;
    });
  }
}

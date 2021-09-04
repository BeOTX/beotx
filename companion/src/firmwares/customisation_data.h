/*
 * Copyright (C) OpenTX
 *
 * Based on code named
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

#pragma once
#include "constants.h"

#include <QtCore>

/*

  Note: this code is consolidated from various radio/src files and modified if necessary to run on desktop

*/

constexpr int MAX_CUSTOM_SCREENS      {5};
constexpr int THEME_NAME_LEN          {8};
constexpr int MAX_THEME_OPTIONS       {5};
constexpr int LEN_ZONE_OPTION_STRING  {8};
constexpr int MAX_LAYOUT_ZONES        {10};
constexpr int MAX_LAYOUT_OPTIONS      {10};
constexpr int WIDGET_NAME_LEN         {10};
constexpr int MAX_WIDGET_OPTIONS      {5};
constexpr int MAX_TOPBAR_ZONES        {4};
constexpr int MAX_TOPBAR_OPTIONS      {1};
constexpr int LAYOUT_ID_LEN           {10};

// Common 'ZoneOptionValue's among all layouts
enum {
  LAYOUT_OPTION_TOPBAR = 0,
  LAYOUT_OPTION_FM,
  LAYOUT_OPTION_SLIDERS,
  LAYOUT_OPTION_TRIMS,
  LAYOUT_OPTION_MIRRORED,

  LAYOUT_OPTION_LAST_DEFAULT=LAYOUT_OPTION_MIRRORED
};

struct ZoneOptionValue  // union in radio/src/datastructs.h
{
  unsigned int unsignedValue;
  int signedValue;
  unsigned int boolValue;
  char stringValue[LEN_ZONE_OPTION_STRING + 1];
};

enum ZoneOptionValueEnum {
  ZOV_Unsigned,
  ZOV_Signed,
  ZOV_Bool,
  ZOV_String,
  ZOV_LAST = ZOV_String
};

inline const char * zoneOptionValueEnumToString(ZoneOptionValueEnum zovenum) {
  switch (zovenum) {
    case ZOV_Unsigned:
      return "unsigned";
    case ZOV_Signed:
      return "signed";
    case ZOV_Bool:
      return "bool";
    case ZOV_String:
      return "string";
    default:
      return "unknown";
  }
}

struct ZoneOption
{
  enum Type {
    Integer,
    Source,
    Bool,
    String,
    File,
    TextSize,
    Timer,
    Switch,
    Color
  };

  const char * name;
  Type type;
  ZoneOptionValue deflt;
  ZoneOptionValue min;
  ZoneOptionValue max;
};

struct ZoneOptionValueTyped
{
  ZoneOptionValueEnum type;
  ZoneOptionValue     value;
};

inline ZoneOptionValueEnum zoneValueEnumFromType(ZoneOption::Type type)
{
  switch(type) {
  case ZoneOption::File:
  case ZoneOption::String:
    return ZOV_String;

  case ZoneOption::Integer:
    return ZOV_Signed;

  case ZoneOption::Bool:
    return ZOV_Bool;

  case ZoneOption::Color:
  case ZoneOption::Timer:
  case ZoneOption::Switch:
  case ZoneOption::Source:
  case ZoneOption::TextSize:
  default:
    return ZOV_Unsigned;
  }
}

struct WidgetPersistentData {
  ZoneOptionValueTyped options[MAX_WIDGET_OPTIONS];
};

struct ZonePersistentData {
  char widgetName[WIDGET_NAME_LEN + 1];
  WidgetPersistentData widgetData;
};

template<int N, int O>
struct WidgetsContainerPersistentData {
  ZonePersistentData   zones[N];
  ZoneOptionValueTyped options[O];
};

typedef WidgetsContainerPersistentData<MAX_LAYOUT_ZONES, MAX_LAYOUT_OPTIONS> LayoutPersistentData;

typedef WidgetsContainerPersistentData<MAX_TOPBAR_ZONES, MAX_TOPBAR_OPTIONS> TopBarPersistentData;

inline void setZoneOptionValue(ZoneOptionValue & zov, bool value)          { zov.boolValue = value; }
inline void setZoneOptionValue(ZoneOptionValue & zov, int value)           { zov.signedValue = value; }
inline void setZoneOptionValue(ZoneOptionValue & zov, char value)          { memset(&zov.stringValue, value, LEN_ZONE_OPTION_STRING); }
inline void setZoneOptionValue(ZoneOptionValue & zov, unsigned int value)  { zov.unsignedValue = value; }

// cannot use QColor so use formula from libopenui_defines.h
#define RGB(r, g, b)    (uint16_t)((((r) & 0xF8) << 8) + (((g) & 0xFC) << 3) + (((b) & 0xF8) >> 3))
#define WHITE           RGB(0xFF, 0xFF, 0xFF)
#define RED             RGB(229, 32, 30)

class RadioTheme
{
  Q_DECLARE_TR_FUNCTIONS(RadioTheme)

  public:
    struct PersistentData {
      ZoneOptionValueTyped options[MAX_THEME_OPTIONS];
    };

    struct ThemeData {
      char themeName[THEME_NAME_LEN + 1];
      PersistentData themePersistentData;
    };

    static void init(const char * themeName, ThemeData & themeData)
    {
      memset(&themeData, 0, sizeof(ThemeData));

      memcpy(&themeData.themeName, themeName, THEME_NAME_LEN);

      PersistentData & persistentData = themeData.themePersistentData;

      persistentData.options[0].type = zoneValueEnumFromType(ZoneOption::Type::Color);
      setZoneOptionValue(persistentData.options[0].value, (unsigned int)WHITE);

      persistentData.options[1].type = zoneValueEnumFromType(ZoneOption::Type::Color);
      setZoneOptionValue(persistentData.options[1].value, (unsigned int)RED);
    }
};

class RadioLayout
{
  Q_DECLARE_TR_FUNCTIONS(RadioLayout)

  public:
    struct CustomScreenData {
      char layoutId[LAYOUT_ID_LEN + 1];
      LayoutPersistentData layoutPersistentData;
    };

    struct CustomScreens {
      CustomScreenData customScreenData[MAX_CUSTOM_SCREENS];
    };

    static void init(const char * layoutId, CustomScreens & customScreens)
    {
      memset(&customScreens, 0, sizeof(CustomScreens));

      for (int i = 0; i < MAX_CUSTOM_SCREENS; i++) {
        if (i == 0)
          memcpy(&customScreens.customScreenData[i].layoutId, layoutId, LAYOUT_ID_LEN);

        LayoutPersistentData & persistentData = customScreens.customScreenData[i].layoutPersistentData;

        int j = 0;
        persistentData.options[j].type = zoneValueEnumFromType(ZoneOption::Type::Bool);
        setZoneOptionValue(persistentData.options[j++].value, (bool)true);

        persistentData.options[j].type = zoneValueEnumFromType(ZoneOption::Type::Bool);
        setZoneOptionValue(persistentData.options[j++].value, (bool)true);

        persistentData.options[j].type = zoneValueEnumFromType(ZoneOption::Type::Bool);
        setZoneOptionValue(persistentData.options[j++].value, (bool)true);

        persistentData.options[j].type = zoneValueEnumFromType(ZoneOption::Type::Bool);
        setZoneOptionValue(persistentData.options[j++].value, (bool)true);

        persistentData.options[j].type = zoneValueEnumFromType(ZoneOption::Type::Bool);
        setZoneOptionValue(persistentData.options[j++].value, (bool)false);
      }
    }
};

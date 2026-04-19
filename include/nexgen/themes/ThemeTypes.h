#pragma once

#include <QString>

namespace nexgen::themes {

enum class ThemeMode {
  System = 0,
  Light = 1,
  Dark = 2
};

struct ThemeId {
  QString id; // e.g. "default", "nexgen_blue"
};

} // namespace nexgen::themes

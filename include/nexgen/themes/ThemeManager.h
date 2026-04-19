#pragma once

#include <QObject>
#include <QPalette>

#include "nexgen/themes/ThemeTypes.h"

class QApplication;
class QSettings;

namespace nexgen::themes {

class ThemeManager final : public QObject {
  Q_OBJECT

public:
  explicit ThemeManager(QObject* parent = nullptr);

  // Settings contract: Org=Nexgen, App=Utilities (host provides QSettings instance)
  void load(QSettings& s);
  void save(QSettings& s) const;

  void applyTo(QApplication& app);

  ThemeMode mode() const { return m_mode; }
  ThemeId themeId() const { return m_themeId; }

  void setMode(ThemeMode mode);
  void setThemeId(ThemeId id);

signals:
  void themeChanged();

private:
  ThemeMode m_mode = ThemeMode::System;
  ThemeId m_themeId{QStringLiteral("default")};

  QPalette buildPalette() const;
};

} // namespace nexgen::themes

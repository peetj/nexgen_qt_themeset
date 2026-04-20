#include "nexgen/themes/ThemeManager.h"

#include <QApplication>
#include <QGuiApplication>
#include <QSettings>
#include <QStyleHints>

namespace nexgen::themes {

static constexpr auto kGroup = "Theme";
static constexpr auto kKeyMode = "mode";
static constexpr auto kKeyThemeId = "themeId";

static bool isSystemDark() {
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
  const auto scheme = QGuiApplication::styleHints()->colorScheme();
  return scheme == Qt::ColorScheme::Dark;
#else
  return false;
#endif
}

ThemeManager::ThemeManager(QObject* parent) : QObject(parent) {}

void ThemeManager::load(QSettings& s) {
  s.beginGroup(kGroup);
  const int modeRaw = s.value(kKeyMode, static_cast<int>(ThemeMode::System)).toInt();
  if (modeRaw < static_cast<int>(ThemeMode::System) || modeRaw > static_cast<int>(ThemeMode::Dark)) {
    m_mode = ThemeMode::System;
    s.setValue(kKeyMode, static_cast<int>(m_mode));
  } else {
    m_mode = static_cast<ThemeMode>(modeRaw);
  }
  m_themeId = ThemeId{ s.value(kKeyThemeId, QStringLiteral("default")).toString() };
  s.endGroup();
}

void ThemeManager::save(QSettings& s) const {
  s.beginGroup(kGroup);
  s.setValue(kKeyMode, static_cast<int>(m_mode));
  s.setValue(kKeyThemeId, m_themeId.id);
  s.endGroup();
}

void ThemeManager::setMode(ThemeMode mode) {
  if (m_mode == mode) return;
  m_mode = mode;
  emit themeChanged();
}

void ThemeManager::setThemeId(ThemeId id) {
  if (m_themeId.id == id.id) return;
  m_themeId = std::move(id);
  emit themeChanged();
}

QPalette ThemeManager::buildPalette() const {
  bool dark = false;
  switch (m_mode) {
    case ThemeMode::Light: dark = false; break;
    case ThemeMode::Dark:  dark = true;  break;
    case ThemeMode::System: dark = isSystemDark(); break;
  }

  // Minimal usable palette. We'll expand with actual theme tokens later.
  if (dark) {
    const QColor window(24, 24, 24, 210);
    const QColor base(18, 18, 18, 255);
    const QColor text(240, 240, 240);
    const QColor disabled(150, 150, 150);

    QPalette p;
    p.setColor(QPalette::Window, window);
    p.setColor(QPalette::WindowText, text);
    p.setColor(QPalette::Base, base);
    p.setColor(QPalette::AlternateBase, QColor(28, 28, 28));
    p.setColor(QPalette::Text, text);
    p.setColor(QPalette::Button, QColor(32, 32, 32));
    p.setColor(QPalette::ButtonText, text);
    p.setColor(QPalette::ToolTipBase, text);
    p.setColor(QPalette::ToolTipText, QColor(20, 20, 20));
    p.setColor(QPalette::Highlight, QColor(70, 120, 255));
    p.setColor(QPalette::HighlightedText, QColor(255, 255, 255));

    p.setColor(QPalette::Disabled, QPalette::WindowText, disabled);
    p.setColor(QPalette::Disabled, QPalette::Text, disabled);
    p.setColor(QPalette::Disabled, QPalette::ButtonText, disabled);
    return p;
  } else {
    QPalette p;
    // Light: set a slightly translucent window so WA_TranslucentBackground looks intentional.
    p.setColor(QPalette::Window, QColor(255,255,255,210));
    p.setColor(QPalette::WindowText, QColor(20,20,20));
    p.setColor(QPalette::ButtonText, QColor(20,20,20));
    p.setColor(QPalette::Text, QColor(20,20,20));

    // Light: consistent highlight.
    p.setColor(QPalette::Highlight, QColor(40, 120, 255));
    p.setColor(QPalette::HighlightedText, QColor(255, 255, 255));
    return p;
  }
}

void ThemeManager::applyTo(QApplication& app) {
  app.setStyle(QStringLiteral("Fusion"));
  app.setPalette(buildPalette());
}

} // namespace nexgen::themes

#include "nexgen/themes/ThemeManager.h"

#include <QApplication>
#include <QSettings>

namespace nexgen::themes {

static constexpr auto kGroup = "Theme";
static constexpr auto kKeyMode = "mode";
static constexpr auto kKeyThemeId = "themeId";

ThemeManager::ThemeManager(QObject* parent) : QObject(parent) {}

void ThemeManager::load(QSettings& s) {
  s.beginGroup(kGroup);
  m_mode = static_cast<ThemeMode>(s.value(kKeyMode, static_cast<int>(ThemeMode::System)).toInt());
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
  // Minimal placeholder palette. We'll replace with your real token set during extraction.
  QPalette p;
  // NOTE: We will likely use Fusion style for consistent rendering.
  // app.setStyle("Fusion"); is applied in applyTo().
  return p;
}

void ThemeManager::applyTo(QApplication& app) {
  // Consistent base across Windows builds.
  app.setStyle(QStringLiteral("Fusion"));
  app.setPalette(buildPalette());

  // TODO: optional small QSS can be applied here.
}

} // namespace nexgen::themes

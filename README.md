# nexgen_qt_themeset

Reusable theming library for Nexgen Qt utilities (Qt Widgets).

## Usage (submodule)

```cmake
add_subdirectory(external/nexgen_qt_themeset)
target_link_libraries(my_app PRIVATE nexgen::qt_themeset)
```

```cpp
QSettings s("Nexgen", "Utilities");

nexgen::themes::ThemeManager tm;
tm.load(s);
tm.applyTo(app);

QObject::connect(&tm, &nexgen::themes::ThemeManager::themeChanged, [&]{
  tm.applyTo(app);
  tm.save(s);
});
```

Settings keys live under the `Theme/` group.

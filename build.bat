@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86

cl /std:c++17 /nologo /W3 /O2 /fp:fast /Gm- /Fedemo.exe /D_CRT_SECURE_NO_DEPRECATE main.cpp gui/lib/font_manager.cpp gui/lib/screen_overlay.cpp gui/lib/screen_gui.cpp gui/lib/screen_overlay_confirm.cpp gui/lib/screen_overlay_textbox.cpp gui/lib/screen_overlay_two_actions.cpp gui/lib/screen_manager.cpp gui/model/driver.cpp gui/model/driver_screen.cpp gui/model/id.cpp gui/screens/screen_driver_menu.cpp gui/screens/screen_drivers.cpp gui/screens/screen_drivers_reorder.cpp gui/screens/screen_edit_screen.cpp gui/screens/screen_param_order.cpp gui/screens/screen_racemode.cpp gui/screens/screen_racemode_screens_select.cpp gui/screens/screen_racemode_status_bar.cpp gui/screens/screen_raceprofile_menu.cpp gui/screens/screen_raceprofiles_reorder.cpp gui/screens/screen_screens_list.cpp gui/screens/screen_settings_buttons.cpp gui/screens/screen_settings_menu.cpp user32.lib gdiplus.lib shlwapi.lib /link /incremental:no
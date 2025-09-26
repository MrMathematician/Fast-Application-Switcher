#include <X11/X.h>
#include <bits/stdc++.h>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <X11/Xatom.h>

#pragma once



class AvailableWindows{
private:
  Display* display;
  Window root;
  long currentDesktop;

  std::vector<Window> currDesktopWindows;

  long get_cardinal_property(Display* display, Window win, const char* propName);
  void initialize();

public:  
  AvailableWindows(Display* display, Window root);

  void focus_previous();
  void focus_next();
};

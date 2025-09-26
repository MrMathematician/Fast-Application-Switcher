#include <X11/X.h>
#include <bits/stdc++.h>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <X11/Xatom.h>

#include "../include/AvailableWindows.h"
#include "../include/switch_prev.h"

void switch_to_prev_window(Display* display, Window root){
  std::cout << "go to prev\n";

  AvailableWindows currAvailableOpened = AvailableWindows(display, root);

  currAvailableOpened.focus_previous();
}



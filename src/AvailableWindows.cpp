#include "../include/AvailableWindows.h"

#include <X11/X.h>
#include <bits/stdc++.h>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <X11/Xatom.h>




  
long AvailableWindows::get_cardinal_property(Display* display, Window win, const char* propName) {
  Atom property = XInternAtom(display, propName, True);
  if (property == None) return -1;

  Atom actualType;
  int actualFormat;
  unsigned long nItems, bytesAfter;
  unsigned char* data = nullptr;

  int status = XGetWindowProperty(
    display, win, property,
    0, 1, False, XA_CARDINAL,
    &actualType, &actualFormat,
    &nItems, &bytesAfter, &data
  );

  if (status == Success && data) {
    long value = *((long*)data);
    XFree(data);
    return value;
  }
  return -1;
}


void AvailableWindows::initialize(){
  currentDesktop = get_cardinal_property(display, root, "_NET_CURRENT_DESKTOP");
  std::cout << "Current workspace index: " << currentDesktop << "\n\n";

  // Get _NET_CLIENT_LIST
  Atom netClientList = XInternAtom(display, "_NET_CLIENT_LIST", True);
  if (netClientList == None) {
    std::cerr << "_NET_CLIENT_LIST not supported by WM\n";
    XCloseDisplay(display);
    return;
  }

  Atom actualType;
  int actualFormat;
  unsigned long nItems, bytesAfter;
  unsigned char* data = nullptr;

  int status = XGetWindowProperty(
    display, root, netClientList,
    0L, (~0L), False, XA_WINDOW,
    &actualType, &actualFormat,
    &nItems, &bytesAfter, &data
  );

  if(status == Success && data){
    Window* windows = reinterpret_cast<Window*>(data);

    for(unsigned long i = 0; i < nItems; i++) {
      long desk = get_cardinal_property(display, windows[i], "_NET_WM_DESKTOP");

      if(desk == currentDesktop) currDesktopWindows.push_back(windows[i]) ;
    }
    XFree(data);
  }
  else std::cerr << "Failed to get _NET_CLIENT_LIST\n";
}

AvailableWindows::AvailableWindows(Display* display, Window root){
  this -> display = display;  
  this -> root = root;

  initialize();
}

void AvailableWindows::focus_previous(){
  Window currFocused;
  int revert_to;

  XGetInputFocus(display, &currFocused, &revert_to);

  Window TARGET;

  for(int i = 0; i < currDesktopWindows.size(); i++){
    if(currDesktopWindows.at(i) == currFocused){
      TARGET = (i - 1 >= 0) ? (currDesktopWindows.at(i - 1)) : (currDesktopWindows.back());
    }
  }
  
  XSetInputFocus(display, TARGET, RevertToNone, CurrentTime);
  XRaiseWindow(display, TARGET);
  XFlush(display);
}

void AvailableWindows::focus_next(){
  Window currFocused;
  int revert_to;

  XGetInputFocus(display, &currFocused, &revert_to);

  Window TARGET;

  for(int i = 0; i < currDesktopWindows.size(); i++){
    if(currDesktopWindows.at(i) == currFocused){
      TARGET = (i + 1 < currDesktopWindows.size()) ? (currDesktopWindows.at(i + 1)) : (currDesktopWindows.front());
    }
  }
  
  XSetInputFocus(display, TARGET, RevertToNone, CurrentTime);
  XRaiseWindow(display, TARGET);
  XFlush(display);
}


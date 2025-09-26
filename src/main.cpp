#include <X11/X.h>
#include <bits/stdc++.h>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <X11/Xatom.h>

#include "../include/switch_next.h"
#include "../include/switch_prev.h"



int main(){
 Display *display = XOpenDisplay(NULL);

  if(!display){
    std::cout << "Couldn't run program. Either you're in TTY, or this is not X11!\n";
    return 1;
  }


  int xIopcode, event, error;
  if(!XQueryExtension(display, "XInputExtension", &xIopcode, &event, &error)){
    std::cout << "Welp, XInput is not available!\n";
    return 1;
  }


  int major = 2, minor = 0;
  if(XIQueryVersion(display, &major, &minor) != Success){
    std::cout << "Welp, XInput 2 is not available!\n";
    return 1;
  }

  Window root = DefaultRootWindow(display);

  XIEventMask evmask;
  unsigned char mask[(XI_LASTEVENT + 7) / 8] = {0};
  evmask.deviceid = XIAllMasterDevices;
  evmask.mask_len = sizeof(mask);
  evmask.mask = mask;

  XISetMask(mask, XI_RawKeyPress);
  XISetMask(mask, XI_RawKeyRelease);


  XISelectEvents(display, root, &evmask, 1);

  int altPressed = 0;

  while(1){
    XEvent event;
    XNextEvent(display, &event);

    if(event.xcookie.type == GenericEvent
    && event.xcookie.extension == xIopcode
    && XGetEventData(display, &event.xcookie)){
      XIRawEvent* rawEvent = (XIRawEvent*) event.xcookie.data;

      int keycode = rawEvent -> detail;

      if(rawEvent -> evtype == XI_RawKeyPress){
        if(keycode == 64 || keycode == 108){
          std::cout << "woah\n";
          altPressed = 1;
        }
        else if(altPressed && keycode == 44){
          switch_to_prev_window(display, root); 
        }
        else if(altPressed && keycode == 45){
          switch_to_next_window(display, root);
        }
      }
      else if(rawEvent -> evtype == XI_RawKeyRelease){
        if(keycode == 64 || keycode == 108){
          altPressed = 0;
        }
      }

      XFreeEventData(display, &event.xcookie);
    }
  }

  XCloseDisplay(display);
  return 0;
}

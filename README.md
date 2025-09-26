# Fast Application Switcher

This application helps you navigate X11 windows in the same workspace faster than
the conventional slow `Alt + Tab` configuration, and instead replaces it with
`Alt + J`, and `Alt + K` which are configured through this program to cycle through
windows in the same workspace left or right similar to window manager monocole
mode.

## Installation
Before you proceed to installation, please note that this only supports X11 applications
and will work only in desktop environments.

1- Open the `include` directory
2- run `chmod +x install.sh`
3- run the `install.sh` script

## Further Description 
Using `Alt + Tab` creates this pop up window that obstructs your workflow while also not maintining 
the same stacking order of the windows. This makes it extremely disorienting when working with multiple applications.
This program emulates the **Monocole mode** commonly found in window managers like Suckless DWM and BSPWM, where you 
can swiftly cycle between windows while maintaing their same stacking order. This feature is unfortunately still not 
supported by most desktop environments, and this is what this project aims to resolve.

## Notes
1- You can easily change the `Alt`, `J` and `K` keys to any keys of your liking in the main.cpp in the control loop.
of using a simple desktop environment.
2- This only works on X11.

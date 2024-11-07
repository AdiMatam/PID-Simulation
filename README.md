# SF-Boilerplate-Project

## A Preface
A series of utilites to manage windows, rendering, animations, and more in SFML. 
In SFML, all window drawing and event-handling is managed in a 'mainloop.' This structure is common to several high-level graphics libraries. However, as projects scale to include numerous assets/screens/utilities, it becomes challenging to maintain a readable structure without bloating the mainloop.

Individual developers specify their own structures/classes to address this problem. This repository attempts to provide a robust set of abstractions and utility methods which make SFML development easy, organized, and scalable

This is very much a work-in-progress...

## High Level Structure

## Pending Developments
- Concurrently manage multiple windows (multi-threading). The App<->WindowManager structure permits multiple windows, but there are threading issues resulting in the non-primary window crashing...
- Robust wrappers around TGUI Widgets. `incompatible/ButtonTextPair` is an example of this. It is _temporarily deprecated_ until the multi-window structure is finalzied
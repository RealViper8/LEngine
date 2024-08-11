#ifndef LUA_FUNCTIONS_H
#define LUA_FUNCTIONS_H

#ifdef __unix__
  #include <X11/Xlib.h>
  #include "X11/keysym.h"
#endif

#include <lua.hpp>

int lua_exit(lua_State *L);
int lua_key_pressed(lua_State *L);

#ifndef OS_Windows
  char get_key_press();
  bool khbit();
  void setRawMode(bool enable);
  int get_key(char *key);
  void setNonBlocking(bool enable);
#endif

#endif

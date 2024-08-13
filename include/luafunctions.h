#ifndef LUA_FUNCTIONS_H
#define LUA_FUNCTIONS_H

#include <lua.hpp>

int lua_exit(lua_State *L);
// int lua_key_pressed(lua_State *L);
int lua_log(lua_State *L);
int lua_log_bold(lua_State *L);

#endif

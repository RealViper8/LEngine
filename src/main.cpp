#include <iostream>
#include <lua.hpp>
#include <memory>

#include "../include/game.h"

int main() {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  std::unique_ptr<config_t> configurations (new configs);
 
  if (FileExists("config.lua") && Check(L, luaL_dofile(L, "config.lua"))) {
    lua_getglobal(L, "conf");
    if (lua_istable(L, -1)) {
      lua_pushstring(L, "name");
      lua_gettable(L, -2);
      configurations->name = lua_tostring(L, -1);
      lua_pop(L, 1);
    }
  }

  if (!FileExists("init.lua")) {
    init_gamefile();
  }
  
  if(Check(L, luaL_dofile(L, "init.lua"))) {
    
  }
}

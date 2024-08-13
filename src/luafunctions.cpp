#include "../include/luafunctions.h"
#include "../include/logger.h"
#include <cctype>
#include <cstdlib>

#include <SDL2/SDL.h>


int lua_exit(lua_State *L) {
  int exit_code = lua_tonumber(L, 1);
  lua_getglobal(L, "exit");
  if(lua_isfunction(L, -1)) {
    lua_pushinteger(L, exit_code);
    lua_pcall(L, 1, 0, 0);
  }
  exit(exit_code);
  return 0;
}

int lua_log(lua_State *L) {
  std::string msg = lua_tostring(L, 1);
  int state = lua_tointeger(L, 2);

  msg_T type;

  switch(state) {
    case 0:
      type = info;
      break;
    case 1:
      type = error;
      break;
    case 2:
      type = warning;
      break;      
  }
  
  Logger logger;
  logger.setBuffer(msg);
  logger.setDebug(false);

  logger.print(type);
  
  return 2;
}

int lua_log_bold(lua_State *L) {

  std::string msg = lua_tostring(L, 1);
  int state = lua_tointeger(L, 2);

  msg_T type;

  switch(state) {
    case 0:
      type = info;
      break;
    case 1:
      type = error;
      break;
    case 2:
      type = warning;
      break;      
  }
  
  Logger logger;
  logger.setBuffer(msg);
  logger.setDebug(false);

  logger.print(type, true);

  return 2;
}

int lua_clear() {
  
  #ifdef OS_Windows
    system("cls");
  #else
    system("clear");
  #endif
  
  return 0;
}

#ifndef GAME_H
#define GAME_H

#include <cstdint>
#include <lua.hpp>
#include <string>
#include <cstring>
#include "luafunctions.h"

#define PREP_ERROR(n, t, m) { (n).type = (t); (n).errormsg = (m); }

typedef struct configs {
  std::string name = "Game";
  uint16_t fps = 60;
  bool terminal = true;
} config_t;

enum file_enum : uint {
  init,
  game,
  config,
  none = 0,
};

enum Error {
  NOT_IMPLEMENTED,
  SYNTAX_ERROR,
  NOT_ENOUGH_ARGUMENTS,
};

typedef struct ERROR_STRUCT {
  char* errormsg;
  enum Error type;
} error;

void print_error(error);

bool Check(lua_State*, int);
bool DirExist(const char*);
bool FileExists(const char*);

void init_gamefile();
void init_file(file_enum);

void tolowerstr(char* str);
void toupperstr(char* str);
#endif

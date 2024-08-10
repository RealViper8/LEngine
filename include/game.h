#ifndef GAME_H
#define GAME_H

#include <lua.hpp>
#include <string>

typedef struct configs {
  std::string name;
} config_t;

typedef enum file_enum : uint {
  init,
  game,
  config,
  none = 0,
} file_t;

bool Check(lua_State*, int);
bool DirExist(const char*);
bool FileExists(const char*);

void init_gamefile();
void init_file();

#endif

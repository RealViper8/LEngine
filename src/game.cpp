#include "../include/game.h"
#include <cstdio>
#include <iostream>
#include <filesystem>
#include <fstream>

bool Check(lua_State *L, int r) {
  if (r != LUA_OK) {
    std::string errormsg = lua_tostring(L, -1);
    std::cout << errormsg << std::endl;
    return false;
  }
  return true;
}

bool DirExist(const char* dirPath) {
  if (std::filesystem::exists(dirPath) && std::filesystem::is_directory(dirPath)) {
    return true;
  } else {
    return false;
  }
}

bool FileExists(const char* filename) {
  if (std::filesystem::exists(filename) && std::filesystem::is_regular_file(filename)) {
    return true;
  } else {
    return false;
  }
}

void init_gamefile() {
  std::ofstream file("init.lua");
  file << "function update()";
  file << "\n\n";
  file << "end";
  
  file << "\n\nfunction start()";
  file << "\n\n";
  file << "end";

  file << "\n\nfunction stop()";
  file << "\n\n";
  file << "end";

  file.close();
}



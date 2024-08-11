#include "../include/game.h"
#include <csignal>
#include <cstdio>
#include <cstring>
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
  file << "run = true\n";
  file << "status_code = 0\n";
  file << "\n-- This function is executed 60 times every frame (if default).i\n";
  file << "function update(deltaTime)\n";
  file << "    print(\"Update was run deltaTime: \" .. deltaTime)\n";
  file << "end\n";
  
  file << "\n-- This function is executed one time.\n";
  file << "function start(game_name)\n";
  file << "    print(\"Starting \" .. game_name)\n";
  file << "    return 0\n";
  file << "end\n";

  file << "\n-- This function is executed when the game exits.\n";
  file << "function exit(exit_code)\n";
  file << "    run = false\n";
  file << "    print(\"Exiting with Exit Code: \" .. exit_code)\n";
  file << "end\n";

  file.close();
}

void init_file(file_enum f) {
  std::ofstream file;
  switch (f) {
    case init:
      init_gamefile();
      break;
    case game:
      file.open("game.lua");
      file.close();
      break;
    case config:
      file.open("config.lua");
      file << "conf = {";
      file << "\n\n";
      file << "}\n";
      file.close();
      break;
  }
}

void tolowerstr(char* str) 
{
  int strlength = strlen(str);
  for (int i = 0; i < strlength; i++) {
    str[i] = std::tolower(str[i]);
  }
}

void toupperstr(char* str) 
{
  for (int i = 0; i < static_cast<int>(strlen(str)); i++) {
    str[i] = std::toupper(str[i]);
  }
}

void print_error(error err) {
  switch(err.type) {
    case SYNTAX_ERROR:
      std::cout << "SYNTAX_ERROR";
      break;
    case NOT_IMPLEMENTED:
      std::cout << "NOT_IMPLEMENTED";
      break;
    case NOT_ENOUGH_ARGUMENTS:
      std::cout << "NOT_ENOUGH_ARGUMENTS";
      break;
  }

  std::cout << "      -> " << err.errormsg << std::endl;
}

error init_err(Error type, char* msg) {
  return error { .errormsg = msg, .type = type };
}

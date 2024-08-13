#include <cstdlib>
#include <iostream>
#include <lua.hpp>
#include <memory>
#include <chrono>
#include <thread>
#include <string>

#include "../include/luafunctions.h"
#include "../include/game.h"

#ifndef OS_Windows
  #include <termios.h>
  #include <unistd.h>
  #include <fcntl.h>
#else
  #include <windows.h>
#endif

#ifndef OS_Windows
char getChar() {
  struct termios oldt, newt;
    char ch = '\0';

    // Get current terminal attributes
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Set terminal to raw mode
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Set terminal to non-blocking mode
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    // Attempt to read a single character
    ssize_t bytesRead = read(STDIN_FILENO, &ch, 1);
    if (bytesRead <= 0) {
        ch = '\0'; // No character read
    }

    // Restore original terminal attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    // Restore original blocking mode
    fcntl(STDIN_FILENO, F_SETFL, flags);

    return ch;
}

#else

void setConsoleMode(bool enable) {
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hConsole, &mode);

    if (enable) {
        // Disable line input and echo input
        mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    } else {
        // Enable line input and echo input (restore default)
        mode |= (ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    }

    SetConsoleMode(hConsole, mode);
}

// Function to get a single character with non-blocking read
char getChar() {
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hConsole, &mode);

    // Set console mode to non-blocking
    setConsoleMode(true);

    // Attempt to read a single character
    INPUT_RECORD inputRecord;
    DWORD eventsRead;
    char ch = '\0';

    if (ReadConsoleInput(hConsole, &inputRecord, 1, &eventsRead)) {
        if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.EventType.KeyEvent.bKeyDown) {
            ch = inputRecord.Event.EventType.KeyEvent.uChar.AsciiChar;
        }
    }

    // Restore console mode
    setConsoleMode(false);

    return ch;
}

#endif

int main(int argc, char** argv) {
  int status_code = 0;
  bool running = true;
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  lua_register(L, "exit_game", lua_exit);
  lua_register(L, "log", lua_log);
  lua_register(L, "log_bold", lua_log_bold);

  enum file_enum file_t = none;

  std::unique_ptr<config_t> configurations (new configs);

  if (FileExists("config.lua") && Check(L, luaL_dofile(L, "config.lua")) && argc < 2) {
    lua_getglobal(L, "conf");
    if (lua_istable(L, -1)) {
      lua_pushstring(L, "name");
      lua_gettable(L, -2);
      if(lua_isstring(L, -1)) configurations->name = lua_tostring(L, -1);
      lua_pop(L, 1);

      lua_pushstring(L, "fps");
      lua_gettable(L, -2);
      if(lua_isnumber(L, -1)) configurations->fps = lua_tonumber(L, -1);
      lua_pop(L, 1);
    }

    lua_pop(L, 1);
  } else if(!FileExists("config.lua") && argc > 1) {
    if (std::strncmp(argv[1], "conf", 3) == 0) {
      file_t = config;
      init_file(file_t);
      return 0;
    }
  }

  // if(strlen(configurations->name.c_str()) == 0)
  //   configurations->name = "Game";

  if (!FileExists("init.lua")) {
    file_t = init;
    init_file(file_t);
  }

  if(Check(L, luaL_dofile(L, "init.lua"))) {
    lua_getglobal(L, "start");

    if(lua_isfunction(L, -1)) {
      lua_pushstring(L, configurations->name.c_str());
      if(lua_pcall(L, 1, 1, 0) != LUA_OK) {
        return lua_tonumber(L, -2);
      }
      if(lua_isnumber(L, -1) && lua_tonumber(L, -1) > 0) {
        std::cout << "Error: start function returned error code\n code -> " << lua_tonumber(L, -1) << std::endl;
        return lua_tonumber(L, -1);
      }
      /*if(Check(L, lua_pcall(L, 1, 1, 0))) {
        on_el_exit(L, lua_tointeger(L, -1));
      }*/
    }
    
  std::thread update([&configurations] (lua_State *L, int *status_code, bool *running) {
                   
    lua_getglobal(L, "update");
    if(lua_isfunction(L, -1)) {
      auto previousTime = std::chrono::high_resolution_clock::now();

      while (running) {
        lua_getglobal(L, "run");
        if(lua_isboolean(L, -1)) *running = lua_toboolean(L, -1);
        lua_pop(L, 1);

        std::string str(1, getChar());
        lua_pushstring(L, str.c_str());
        lua_setglobal(L, "pressed_key");
        
        lua_getglobal(L, "update");
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - previousTime;
        float deltaTime = elapsedTime.count();

        lua_pushnumber(L, deltaTime);
        if (!Check(L, lua_pcall(L, 1, 0, 0))) break;
        
        previousTime = currentTime;

        const float frameDuration = 1.0f/configurations->fps;
        
        std::chrono::duration<float> frameTime = std::chrono::high_resolution_clock::now() - currentTime;
        if (frameTime.count() < frameDuration) {
            std::this_thread::sleep_for(std::chrono::duration<float>(frameDuration - frameTime.count()));
        }
      }

      
      if(*running == false) {
        lua_getglobal(L, "status_code");
        if(lua_isnumber(L, -1)) *status_code = lua_tonumber(L, -1);
        //std::cout << "EXITED WITH STATUS CODE: " << *status_code << std::endl;
        lua_pop(L, 1);
      }

      lua_pop(L, 1);
    }

    }, L, &status_code, &running);

    update.join();

    lua_getglobal(L, "exit");
    if(lua_isfunction(L, -1)) {
      lua_pushnumber(L, status_code);
      if(Check(L, lua_pcall(L, 1, 0, 0))) {}
    }
  }

  lua_close(L);
  return 0;
}


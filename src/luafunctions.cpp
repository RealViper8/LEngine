#include "../include/luafunctions.h"
#include "../include/logger.h"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <thread>

#if defined( __unix__) || defined(linux)
  #include <unistd.h>
  #include <termios.h>
  #include <fcntl.h>
  #include <sys/select.h>
  #define OS_unix
#elif defined(_WIN32) || defined(WIN32)
  #include <conio.h>
  #define OS_Windows
#endif

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

#ifndef OS_Windows
void setNonBlocking(bool enable) {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    if (flags == -1) {
        std::cerr << "Failed to get file descriptor flags" << std::endl;
        return;
    }

    if (enable) {
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    } else {
        fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
    }
}

void setRawMode(bool enable) {
    static struct termios oldt, newt;

    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

bool khbit() {
  struct timeval tv = {0, 0};
  fd_set readfds;

  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);

  return select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &tv) > 0;
}

char get_key_press() {
  char ch;
  read(STDIN_FILENO, &ch, 1);
  return ch;
}

int get_key(char *key) {
  switch(toupper(*key)) {
    case 'A':
      return 65;
    case 'B':
      return 66;
   case 'C':
      return 67;
    case 'D':
      return 68;
    case 'E':
      return 69;
    case 'F':
      return 70;
    case 'G':
      return 71;
    case 'H':
      return 72;
    case 'I':
      return 73;
    case 'J':
      return 74;
    case 'K':
      return 75;
    case 'L':
      return 76;
    case 'M':
      return 77;
    case 'N':
      return 78;
    case 'O':
      return 79;
    case 'P':
      return 80;
    case 'Q':
      return 81;
    case 'R':
      return 82;
    case 'S':
      return 83;
    case 'T':
      return 84;
    case 'U':
      return 85;
    case 'V':
      return 86;
    case 'W':
      return 87;
    case 'X':
      return 88;
    case 'Y':
      return 89;
    case 'Z':
      return 90;
    default:
      return 0;
  }
}
#endif

int lua_key_pressed(lua_State *L) {

  char key = '0';
  bool pressed = false;

  std::thread key_press_event([] (char *key, bool *pressed, lua_State *L) {
    setNonBlocking(true);
    char key_to_press = lua_tostring(L, 1)[0];
    #ifdef OS_Windows
      key=getch();
      int ascii_value=key;

      if(key == key_to_press) pressed = true;
    #else
      setRawMode(true);
      *key = get_key_press();
      *pressed = (*key == key_to_press) ? true : false;
      //std::cout << *key << " " << *pressed << std::endl;
      setRawMode(false);
      setNonBlocking(false);
    #endif
  }, &key, &pressed, L);

  // std::cout << key << " " << pressed << std::endl;
  key_press_event.join();
  lua_pushboolean(L, pressed);

  return 1;
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

int lua_clear(lua_State *L) {

  #ifdef OS_Windows
    system("cls");
  #else
    system("clear");
  #endif
  
  return 0;
}

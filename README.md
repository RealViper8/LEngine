# LEngine

A lua Lightweight Game Engine made with C++ for easy development.

## Build

If you want to build it from source:

**Requirements**:
-> CMake
-> C++

**Supported**
For now LEngine only works on linux.
And it also works on Windows but it contains bugs.

Steps:

1. Clone the repo (git clone)
2. cmake -B build
3. cmake --build build

## Usage

To use this simple engine with lua you will need to compile the project or download a release.
After you have that just run the executable file it will create a init.lua in there you can put your own code
in the functions update and start and close. You can use the basic functions [Refrence Lua](https://www.lua.org/manual/5.3/manual.html#6.1).

## Configurations

You can configure this engine easily by running it with an conf as argument.

Example on linux: `el conf`

Example on windows: `el.exe conf`

## Some config attributes:

name : string

fps : int

Examples of a config.lua file:

```
    conf = {
        name = "Game",
        fps = 60,
    }
```

## Documentation

## Functions:

    exit_game(0)
        -> Takes one integer as parameter.
        -> To exit out of the game with an error_code.
        Example: exit(0)
    key_pressed('w')
        -> Takes one character as parameter.
        -> To check if a key has been pressed (Case Sensitive).
        Example: if key_pressed('o') print("o has been pressed")
    log("hello", 0)
        -> Takes a string and an integer as parameter.
        -> Logs messages first parameter is the message and the second is an integer.
        Examples:
            log("hello", 0) # prints out hello with info log format
            log("no error", 1) # prints out no error with error log format
            log("this is a warning", 2) # prints out this is a warning with warning log format
    log_bold("hello", 0)
        -> Takes a string and an integer as parameter.
        -> Logs messages first parameter is the message and the second is an integer.
        Examples:
            log_bold("hello", 0) # prints out hello with info log format and is bold
            log_bold("no error", 1) # prints out no error with error log format and is bold
            log_bold("this is a warning", 2) # prints out this is a warning with warning log format and is bold

## Credits

if you would like to embed this engine it would be easy to do so.

Made with the Lua C API -> [Lua](https://lua.org)

Made by RealViper.

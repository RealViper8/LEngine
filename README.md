# REngine API
A lua engine made with C++ for easy development.

## Build
If you want to build it from source:


__Requirements__:
    -> CMake
    -> C++

__Supported__
For now LEngine only works on linux.
And it also works on Windows but it contains bugs.

Steps:
1. Clone the repo (git clone)
2. cmake -B build
3. cmake --build build

## Use
To use this simple engine with lua you will need to compile the project or download a release.
After you have that just run the executable file it will create a init.lua in there you can put your own code
in the functions update and start and close.

## Configurations
You can configure this engine easily by running it with an conf as argument.
Example on linux: ```el conf```
Example on windows: ```el.exe conf```

Some config attributes:
--
name : string
fps : int
terminal : bool

Examples of a config.lua file:
```
    conf = {
        name = "Game",
        fps = 60,
    }
```

## Documentation

## Functions:
    exit_game
        -> Takes one integer as parameter.
        -> To exit out of the game with an error_code.
        Example: exit(0)
    key_pressed
        -> Takes one character as parameter.
        -> To check if a key has been pressed (Case Sensitive).
        Example: if key_pressed('o') print("o has been pressed")

## Credits
if you would like to embed this engine it would be easy to use.
Made with the Lua C API -> (Lua)[https://lua.org] 

Made by RealViper.

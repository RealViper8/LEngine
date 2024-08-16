---
sidebar_position: 1
---

import Tabs from '@theme/Tabs';
import TabItem from '@theme/TabItem';

# LEngine

Let's discover the power of LEngine.

## Getting Started

Get started by **compiling the binaries**.

Or **downloading prebuilt binaries** from **[Releases](https://github.com/RealViper8/LEngine/releases)**.

### What you'll need

- [CMake](https://cmake.org/download/) version 3.10 or above:
  - When installing CMake, its recommended to check all checkboxes related to path, dependencies.
- [Make](https://www.gnu.org/software/make/) version 3.82 or above:
  - When installing Make, make sure to add it to path.
- [gcc/g++](https://gcc.gnu.org/install/download.html):
  - When installing gcc make sure to also add it to path.

## Building from Source

To build LEngine from source its quite easy to do so.

:::caution
The Plattform Windows is still in development, it is recommended to use [WSL](https://learn.microsoft.com/en-us/windows/wsl/install)
:::

<Tabs>

 <TabItem value="linux" label="Linux | WSL">

In the current directory of the project run these commands.

```bash
make
cmake -B build
cmake --build build
```

 </TabItem>

 <TabItem value="windows" label="Windows">

In the current directory where the repository is run these commands.

```bash
cmake -B build
cmake --build build
```

 </TabItem>

</Tabs>

### Explanation:

- **`Engine_Lua`**: Represents the root of the directory.
- **`├──build`**: Represents the build folder where executables and object files are stored.
- **`├──init.lua`**: Represents the entry point of the game where the games logic gets written.
- **`├──config.lua`**: Represents the configs file that is optional to change the Games appereance.
- **`└──docs`**: Represents the documentation source files.

## Start your game

Run your own game based on entry point `init.lua` and **(optional)** `config.lua`:

<Tabs>

 <TabItem value="in_repo" label="In Repository">

if you want to just get started compiling and running your own game from the repository you will need to have a `init.lua` and optionally a `config.lua`.

Just run if you already build it. [How to Build?](#building-from-source)

### Linux

```bash
./build/el
```

The `./build/el` command **runs** the executable file `el` in `build` directory.

### Windows

```sh
./build/el.exe
```

 </TabItem>

 <TabItem value="out_repo" label="Custom Folder">

if you want to start your game from a diffrent directory you would need to first [Build from Source](#building-from-source) if you didnt already do that.

Then you need to copy the executable into the directory where you want your game to be.

### Linux

```bash
mv ./build/el <path_to_game>
cd <path_to_game>
./el
```

The `mv` command **moves** the file to an other directory.

### Windows

```bash
move ./build/el.exe <path_to_game>
cd <path_to_game>
./el.exe
```

The `move` command **moves** the file to an other directory.

 </TabItem>

</Tabs>

The `cd` command changes the directory you're working with. In order to run your game, you'll need to navigate the terminal there.

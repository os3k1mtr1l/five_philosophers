# Five_philosophers

Graphical visualisation to five dining philosophers synchronization problem.

Preview:
![preview](/github/preview.gif)

Once program being executed the configuration file will appear in the same directory with default parameters. Use it for experementing with adjusting timings between two states (`Thinking` and `Eating`) and how many could there be.

Feel free to try implementing your own synchronization mechanism in `dining_room.cpp` and `dining_room.h`.

## Requirements

This project is designed **exclusively for Windows (64-bit)** and supports **MinGW (GCC)** and **MSVC (Visual Studio)** compilers.  
It primarily uses the **C++20** standard.

## Clone

This repository uses a submodule that contains all third-party dependencies required for the project to work.

To clone the repository with submodules, use:
```bash
git clone --recurse-submodules https://github.com/os3k1mtr1l/five_philosophers
```

If you already cloned the repository without the --recurse-submodules flag, run the following inside the project directory:
```bash
git submodule update --init --recursive
```

You can find the submodule repository here [\*click\*](https://github.com/os3k1mtr1l/game_third_party_module)

## Building

Before building the project, you need to generate the project files using **Premake5**.  
You can find `premake5` in the `vendor/` folder or download it from the official [website](https://premake.github.io/) or [GitHub releases](https://github.com/premake/premake-core).  

### Generating project files
Open `cmd` or PowerShell and navigate to the folder containing `premake5.lua`, then run:

#### For Visual Studio (`vs2022` or other versions)
```bash
premake5 vs2022
```
**Note:** The `vs2022` argument depends on your installed version of Visual Studio. Adjust accordingly.  

#### For MinGW (`mingw32-make`)
```bash
premake5 gmake
```

### *Building the project
After generating the project files, **build the project** using one of the following methods:

Visual Studio 
- Open the generated solution (`.sln` file).  
- Press `F5` to build and run the project.  

MinGW (`mingw32-make`)
- Run `mingw32-make` in the terminal:
```bash
mingw32-make
```
- Optionally, use `help` as a parameter to see available build options.

### Finally
After a successful build, the compiled binaries will be located in the `bin/` folder under the corresponding configuration (`Debug` or `Release`).

## Third party
This project uses the following dependencies:

- [**Premake5**](https://github.com/premake/premake-core) – for project file generation.  
- [**Raylib**](https://github.com/raysan5/raylib) – the main rendering and game engine library.
- [**nlohmann/json**](https://github.com/nlohmann/json) – a modern C++ JSON parser. Used for handling configurations, localization data, and more.
- [**Dear ImGui**](https://github.com/ocornut/imgui) – a fast, self-contained immediate-mode GUI system for debugging tools, editors, and development interfaces.
- [**rlImGui**](https://github.com/raylib-extras/rlImGui) – Raylib-specific backend for `Dear ImGui`.
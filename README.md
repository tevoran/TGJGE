# TGJGE

Welcome this is a 2D game engine called TGJGE. It simply stands for T3V's Game Jam Game Engine.
The engine is written in C with OpenGL3.3 to get the biggest compatibility possible. This way
it is easily usable in C and C++.

You are free to use/modify/distribute the engine for your games or projects. But please act
accordingly to the GPLv3 license which you can read in this repository.

## Dependencies

The game engine is designed to have light dependencies and a high portability across various
platforms. Therefore you only need SDL2, GLEW and OpenGL3.3 available on your system to compile the
engine with a C99 compiler.

### Compilation

I try to make the compilation as portable as possible. This is why I try to avoid subdirectories
in the src directory. This way you need less work to configure your compiler.

To get the current version of the repo just use the following two
git commands.

```
git@github.com:tevoran/TGJGE.git
git submodule update --init --recursive
```
#### Linux

For Linux I have prepared a handy little makefile.

Just run
```
make && make run
```

for a compilation and a quick execution of the test executable which contains whatever I am currently
working on.


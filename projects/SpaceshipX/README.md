## SpaceshipX
This game SpaceshipX is written in C language. This was a school project to learn SDL2 library by using it. 

## Usage
In order to to be able to run this game you should install sdl2 C libraries:
on debian based:
``` bash
$ sudo apt install libsdl2-2.0-0 libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dev
```
on arch based:
``` bash
$ sudo pacman -S sdl2 sdl2_image sdl2_ttf
```
To run the associated binary:
``` bash
$ ./SpaceshipX
```
If you want to recompile it yourself use:
``` bash
$ gcc game.c functions.c -lSDL2 -lSDL2_image -lSDL2_ttf -Wall -o SpaceshipX
```

## Tasks

1. Add obstacles.
2. Add a quit/tryagain menu.
3. Add a score counter.
4. Fix my aweful code.
5. Have fun.

## Resources
[SDL2 library documentations](https://wiki.libsdl.org)

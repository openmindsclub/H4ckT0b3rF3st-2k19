# 2048-cli

This is an implementation of the famous game 2048 written in C
Using the library "ncurses" which is a library that provides
a "GUI-like" interface that runs under a terminal.

## Usage
Ncurses is not a built-in library, so you need to install it.<br/>

On Ubuntu/Debian

```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

On Fedora/CentOs/RHEL:

```bash
sudo dnf install ncurses-devel
```

On Archlinux/Manjaro
```bash
sudo pacman -S ncurses
```

then

```bash
gcc main.c extra.c -o 2048 -lncurses -lm
```

If everything went well, run it

```bash
./2048
```


## Gameplay

The rules of the 2048 game are quite simple you
just need to combine tiles that have the same value
to make another tile with larger number.<br/>
the goal is to create a tile with the number 2048.
However you can still play the game until you lose.

Press arrows to make a move.<br/>
Press 'q' to quit the game.<br/>
Press 'r' to reset the game.<br/>
----- TODO ----------<br/>
Press 'u' to UNDO the move you just did.<br/>
Press 'p' to exit the game BUT save the state<br/>

## Tasks

1. Save top 5 high scores in a file.
2. Add a nice menu to the game
    - Start the game, with three modes (4x4 , 5x5 , 6x6)
    - How to play
    - High scores
    - Exit

3. Add UNDO move, to go back before the actual move.
   (Help yourself with save_board function)

4. Save the state of the game when you quit, and load it
   when you run the game again. (use 'p' key)

PS: you can change game mode (4x4, 5x5,6x6) by changing value of constant NB in constants.h

### Enjoy !!!

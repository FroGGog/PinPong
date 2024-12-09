# PinPong
![Language (C++)](https://img.shields.io/badge/powered_by-C++-brightgreen.svg?style=flat-square) 

A classic pinpong game made in C++ using sfml library.

## Controls

Use **WS** to control player's panel. Other panel is controlled by bot, that trying to predict ball
trajectory.

## Screenshots
![Screenshot](Screenshots/g_start.png?raw=true "Start of game")

![Screenshot](Screenshots/g_inProgress.png?raw=true "Few points later")

### Must Have (dependencies)
- A valid C++ compiler - clang, gcc, msvc that supports c++17
- cmake >= v3.15

## Building

The CMAKE is set up to automatically download the dependencies and link against it. It will be done when configuring cmake.

```
git clone https://github.com/FroGGog/PinPong.git
cd Chess
cmake build .
```


Feel free to fork, fix the issues and contribute. Help is always welcome.
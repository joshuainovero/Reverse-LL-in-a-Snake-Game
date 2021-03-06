# Reversing a Linked List in a Snake Game :snake: #
A snake game that I built in C++ with the implementation of doubly linked list.<br></br>
This small project was inspired by Clément Mihailescu, who have also built a snake game by reversing
a linked list using react JS. His video is in this link: https://www.youtube.com/watch?v=7Rkib_fvowE

## Graphics Library ##
- <a href="https://github.com/SFML/SFML">SFML</a>

## Local Setup ##
Only necessary if you want to tweak the code. Go to <a href="https://github.com/joshuainovero/Reverse-LL-in-a-Snake-Game/releases/tag/1.0">Release</a> for direct gameplay.
1. Clone the repository
```sh
https://github.com/joshuainovero/Reverse-LL-in-a-Snake-Game.git
```
2. If you do not have Mingw-w64 installed on your computer. You can download it on the link below: <br>
<a href="https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download">Download Mingw-w64</a>

3. Go to the parent directory of the repository and type this command:
```sh
mingw32-make
```
This will compile all the source code and output its executable to SnakeGame/output folder.

# Actual Gameplay #
Red apple - Snake growth<br><br>
![red](https://user-images.githubusercontent.com/78135477/125895090-9f05bf29-dc28-4919-b96e-cd45d73ec55b.png)
<br><br><br>
Purple apple (20% chance of spawning) - Snake growth + reversing the snake<br><br>
![purple](https://user-images.githubusercontent.com/78135477/125894963-c2694c43-9692-48f6-93a3-289c695d7a87.png)


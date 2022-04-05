# <img src="assets/chessmate.png" alt="chessmate" width="3%"/> Chess Game in C++

[![Linux](https://svgshare.com/i/Zhy.svg)](https://docs.microsoft.com/en-us/windows/wsl/tutorials/gui-apps)
[![GitHub license](https://img.shields.io/github/license/ThomasByr/chess)](https://github.com/ThomasByr/chess/blob/master/LICENSE)
[![GitHub commits](https://badgen.net/github/commits/ThomasByr/chess)](https://GitHub.com/ThomasByr/chess/commit/)
[![GitHub latest commit](https://badgen.net/github/last-commit/ThomasByr/chess)](https://gitHub.com/ThomasByr/chess/commit/)
[![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)](https://GitHub.com/ThomasByr/chess/graphs/commit-activity)

[![GitHub version](https://badge.fury.io/gh/ThomasByr%2Fchess.svg)](https://github.com/ThomasByr/chess)
[![Author](https://img.shields.io/badge/author-@ThomasByr-blue)](https://github.com/ThomasByr)

<summary>School project</summary>

> [Project instruction paper](https://moodle.unistra.fr/pluginfile.php/748157/mod_resource/content/11/td-echecs.html) (subject) on the Moodle page.

**If you ever get this in .7z, .zip, .tar.gz, .rar or whatever archive format, please ensure you do have the latest version by paying a visit to [the home repo](https://github.com/ThomasByr/chess) on GitHub !**

*note* : doxygen actually can't deal with new markdown GitHub style... please view this page on a proper web editor or even better, on GitHub

1. [In short](#in-short)
2. [Prerequisites](#prerequisites)
3. [Usage](#usage)
4. [F.A.Q.](#faq)
5. [Changelog](#changelog)
6. [Bugs & TODO](#bugs--todo)

## In short

This is a school small project for OOP : a chess game in the command-line. It has some additional features (color map, minimax algorithm).

## Prerequisites

This project currently has no prerequisites but to have a recent enough distribution of Linux. To run tests (as well as the debug mode), valgrind is necessary. You will need doxygen installed in order to build the html version of the documentation. The current makefile is set for g++-11 and the znver3 micro-architecture (Ryzen Zen3), you should modify it if needed.

## Usage

Compile and run a release version with

```bash
make run-release
```

Alternatively `make release` will produce a release version of the executable, `make debug` a debug one, `make run-release` will compile and then run a release version, `make run-debug` will compile and run a debug version with valgrind, `make docs` will trigger doxygen and finally `make` builds a release version and updates the doc. You can run an existing executable with `make run`, and clean with `make clean`.

Moves should be typed in the command line (the program should be asking for it though). Moves are defined by the starting position and the end position, for example b1c3 which would (at the beggining of the game) move the white knight. To play a sample game, please type `make run < tests/play.txt` and then hit enter. To only view error messages on auto-play, please redirect standard output (only) `... > /dev/null` as all errors are thrown to standard error.

Since v0.1.0, some optional arguments can be typed in the command line from `"f:m:n:vqhV"`. At the time of writing, only vqhV are implemented but that is susceptible to change. Arguments have a short and a long version, please type `./bin/echecs --help` to learn more.

The list of known and supported move patterns is as follow :

| move typed                                                                                                     | action                                        |
| -------------------------------------------------------------------------------------------------------------- | --------------------------------------------- |
| <details><summary>`e2e4`</summary>or `e2 e4` or `e2 to e4` or `e2 -> e4`</details>                             | move a piece                                  |
| <details><summary>`queenside castle`</summary>or `castle queenside` or `O-O-O` or `0-0-0` or `o-o-o`</details> | castle queenside                              |
| <details><summary>`kingside castle`</summary>or `castle kingside` or `O-O` or `0-0` or `o-o`</details>         | castle kingside                               |
| <details><summary>` `</summary>or `best` or `b`</details>                                                      | the computer will play the best move for you  |
| <details><summary>`worst`</summary>or `w`</details>                                                            | the computer will play the worst move for you |
| <details><summary>`pass`</summary>or `p`</details>                                                             | to immediately change turn without playing    |
| <details><summary>`rate`</summary>or `r`</details>                                                             | to rate the current position                  |

## F.A.Q.

1.  <details><summary>Why in the world is there no gui here yet ?</summary>

    Well at first, this is a school small project and so we are restricted by the subject paper in a variety of manners. Games should be able to be played through the command line, and to program both interfaces is maybe a little to much to ask knowing that professors won't give a damn into it.
    </details>

2.  <details><summary>Why C++ and not C# ot Java ?</summary>

    Apparently, coding a small "game" in cpp is just much more pleasant than doing it in cs or java, even if super tools like unity exist... cs is just not a thing the french educational system, but unreal engine isn't taught here either so we are just here pretending coding a 2d game in the terminal in cpp is a real thing out there in the world. And don't get me started on sdl2... this isn't even a game engine and is slower than my dead grandmother.
    </details>

3.  <details><summary>It at least has an AI to it right ?</summary>

    Well about that... That is not even on the damn paper. I, however, am going to try my best and implement it even though you can rest assured that it won't bring any bonnuses. The subject paper is just about implementing the right pieces movements for two human players, which is quite boring and serves no purpose.
    </details>

4.  <details><summary>Serious question this time, what is the algorithm I am playing against ?</summary>

    Well, at the time of writing, there is no AI yet, but simple evaluation functions are a thing and this shouldn't be a huge deal implementing a crude search in a tree. Alpha-beta pruning is an optimization I am looking up to, as well as move ordering. So no AI here, as it is a python thing (I wouldn't be surprised though if we were taught AI in c).
    </details>

5.  <details><summary>The project does not even compile, are you for real ?</summary>

    My guess is you did not setup g++ properly through the makefile. Compiling with -Wall -Wextra -Wpedantic should be enough to say that if it compiles on my computer, it should compile everywhere. Oh well... you can argue about that c++ standard that I use, and you could be right. Please make sure the micro-architecture -march= is right for your machine. If you are not sure, either use -march=native or remove the argument completely. Also, -std=c++20 may not be available on g++-9 and lower verions. As I assume copy constructors and some default constructors are automatically setup for you, please use -std=c++17 or higher instead if you encounter any issues.
    </details>

## Changelog

Please refer to the [changelog.md](changelog.md) file for the full history.

<details>
    <summary> v0.1.0 : first release package version (click here to expand) </summary>

*   app class
*   command line arguments from "f:m:n:vqhV" (`./bin/echecs --help` to learn more)

</details>

## Bugs & TODO

Bugs (final correction version)

*   ~~AI is actually stupid, supposed bug on get_legal_moves on pieces~~ (v0.0.2)

TODO (first implementation version)

*   command line options (file input)
*   ~~piece cemetery (piece symbol, times taken, for both players)~~ (v0.0.2)
*   ~~move ordering~~ (basic move ordering v0.0.2)
*   Zobrist Hashing for transpositions (this technique allows to update hash rather than computing it every time)
*   improve pawn structure on the board
*   opening book
*   endgame
*   iterative deepening (store best move first for next iteration)
*   pawn promotion

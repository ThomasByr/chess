# Chess Game in C++

> Project [instruction paper (subject)](https://moodle.unistra.fr/pluginfile.php/748157/mod_resource/content/11/td-echecs.html) on the Moodle page.

1. [In short](#in-short)
2. [Prerequisites](#prerequisites)
3. [Usage](#usage)
4. [F.A.Q.](#faq)
5. [Changelog](#changelog)
6. [Bugs & TODO](#bugs--todo)

## In short

This is a school small project for OOP : a chess game in the command-line. It has some additional features (color map, minimax algorithm).

## Prerequisites

This project currently has no prerequisites but to have a recent enough distribution of Linux. To run tests (as well as the debug mode), valgrind is necessary. The current makefile is set for g++-11 and the znver3 micro-architecture (Ryzen Zen3), you should modify it if needed.

## Usage

Compile and run a release version with

```bash
make run-release
```

Alternatively, you can compile with `make` and run an existing executable binary with `make run`.

Moves should be typed in the command line (the program should be asking for it though). Moves are defined by the starting position and the end position, for example b1c3 which would (at the beggining of the game) move the white knight.

## F.A.Q.

1.  <details><summary>Why in the world is there no gui here yet ?</summary>

    Well at first, this is a school small project and so we are restricted by the subject paper in a variety of manners. Games should be able to be played through the command line, and to program both interfaces is maybe a little to much to ask knowing that professors won't give a damn into it.
    </details>

2.  <details><summary>Why C++ and not C# ot Java ?</summary>

    Apparently, coding a small "game" in cpp is just much more pleasant than doing it in cs or java, even if super tools like unity exist... cs is just not a thing the french educational system, but unreal engine isn't taught here either so we are just here pretending coding a 2d game in the terminal in cpp is a real thing out there in the world.
    </details>

3.  <details><summary>It at least has an AI to it right ?</summary>

    Well about that... That is not even on the damn paper. I, however, am going to try my best and implement it even though you can rest assured that it won't bring any bonnuses. The subject paper is just about implementing the right pieces movements for two human players, which is quite boring and serves no purpose.
    </details>

4.  <details><summary>Real question this time, what is the algorithm I am playing against ?</summary>

    Well, at the time of writing, there is no AI yet, but simple evaluation functions are a thing and this shouldn't be a huge deal implementing a crude search in a tree. Alpha-beta pruning is an optimization I am looking up to, as well as move ordering. So no AI here, as it is a python thing (I wouldn't be surprised though if we were taught AI in c).
    </details>

## Changelog

Please refer to the [changelog.md](changelog.md) file for the full history.

<details>
    <summary> v0.0.2 : improving AI (click here to expand) </summary>

*   finding bugs on copy is going to take a while

</details>

## Bugs & TODO

*   AI is actually stupid, supposed bug on get_legal_moves on pieces

# Chess Game in C++

> Project [instructions](https://moodle.unistra.fr/pluginfile.php/748157/mod_resource/content/11/td-echecs.html) on the Moodle page.

1. [In short](#in-short)
2. [Prerequisites](#prerequisites)
3. [Usage](#usage)
4. [F.A.Q.](#faq)
5. [Changelog](#changelog)
6. [Bugs & TODO](#bugs--todo)

## In short

## Prerequisites

## Usage

Compile and run a release version with

```bash
make run-release
```

Alternatively, you can compile with `make` and run an existing executable binary with `make run`.

Moves should be typed in the command line (the program should be asking for it though). Moves are defined by the starting position and the end position, for example b1c3 which would (at the beggining of the game) move the white knight.

## F.A.Q.

1.  Why in the world is there no gui here yet ?

    Well at first, this is a school small project and so we are restricted by the subject in a variety of manners. Games should be able to be played through the command line, and to program both interfaces is maybe a little to much to ask knowing that professors won't give a damn into it.

2.  Why C++ and not C# ot Java ?

    Apparently, coding a small "game" in cpp is just much more pleasant than doing it in cs or java, even if super tools like unity exist... cs is just not a thing the french educational system, but unreal engine isn't taught here either so we are just here pretending coding a 2d game in the terminal in cpp is a real thing out there in the world.

3.  It at least has an AI to it right ?

    Well about that... That is not even on the damn paper. I, however, am going to try my best and implement it even though you can rest assured that it won't bring any bonnuses. The subject paper is just about implementing the right pieces movements for two human players, which is quite boring and serves no purpose.

4.  Real question this time, what is the algorithm I am playing against ?

    Well, at the time of writing, there is no AI yet, but simple evaluation functions are a thing and this shouldn't be a huge deal implementing a crude search in a tree. Alpha-beta pruning is an optimization I am looking up to, as well as move ordering. So no AI here, as it is a python thing (I wouldn't be surprised though if we were taught AI in c).

## Changelog

Please refer to the [changelog.md](changelog.md) file for the full history.

<details>
    <summary> v0.0.1 : well... seems like I already did it (click here to expand) </summary>

*   port from previous repo in python
*   better v classes so the computer can plan against the player
*   did it in rust... am translating

</details>

## Bugs & TODO

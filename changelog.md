# Changelog

<summary>the full history or so was I told...</summary>

> "Lazyness is nothing more than the habit of resting before you get tired." - the Sole Survivor

## Pre alpha release

**v0.0.1** well... seems like I already did it

- port from previous repo in python
- better v classes so the computer can plan against the player
- did it in rust... am translating
- added some pre-defined class in lib to avoid making a whole new file just to avoid circular imports (because we include files and not features in cpp...)
- all files ready, no undefined references left

**v0.0.2** improving AI

- finding bugs on copy is going to take a while
- valgrind is crying : millions of pieces are created and are not freed by the os... god dammit ubuntu
- added the ending string which is not even standard notation (I called it FEN anyway)
- found a bug on get_weighted_value for pieces
- hopefully copilot can generate doxygen
- found a bug on generated based king position for white player

**v0.0.3** accelerating search

- move ordering has reduced move evaluation by 10 times just by putting attacks before
- avoided the access (when possible on pointers) to direct members of classes

## Beta first minor release

**v0.1.0** first release package version

- app class
- command line arguments from `"f:m:n:vqhVL"` (`./bin/chess --help` to learn more)
- released a compatibility mode for gnu++17 (c++17)
- makefile does not use g++11 explicitly
- github workflow for security checks
- added signal handling and async input
- minor improvement of the evaluation function
- added basic endgame detection and alternate king map
- implemented pawn promotion for additional target pieces (ask for user input)
- as user is requested an additional input, cpu can only promote to queen as of now (there could still be bugs)
- async input reduced, sigint sent by user does not always close the app
- added simple display tweak, user can switch filling up white pieces for display
- add pop command to go to the previous board if available (not recoverable)
- global state of the program is registered

**v0.1.1** more functionalities and patches

- use of standard assert library
- added better starting fen handle (turn, castling rights, en passant)

**v0.1.2** towards next stable release

- renamed executable to something more english
- updated dependencies
- makefile uses specific micro architecture and c++20 since ubuntu 22.04 stable release
- more fitting time/duration display
- manual copy in makefile of the assets folder into html to display images

**v0.1.3** dumped null pointers for nullopt

- use of `std::optional<T>` (c++17 feature)

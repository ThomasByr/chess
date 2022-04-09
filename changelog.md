# Changelog

<summary>the full history or so was I told...</summary>

> "Lazyness is nothing more than the habit of resting before you get tired." - the Sole Survivor

1.  **v0.0.1** well... seems like I already did it
    - port from previous repo in python
    - better v classes so the computer can plan against the player
    - did it in rust... am translating
    - added some pre-defined class in lib to avoid making a whole new file just to avoid circular imports (because we include files and not features in cpp...)
    - all files ready, no undefined references left
2.  **v0.0.2** improving AI
    - finding bugs on copy is going to take a while
    - valgrind is crying : millions of pieces are created and are not freed by the os... god dammit ubuntu
    - added the ending string which is not even standard notation (I called it FEN anyway)
    - found a bug on get_weighted_value for pieces
    - hopefully copilot can generate doxygen
    - found a bug on generated based king position for white player
3.  **v0.0.3** accelerating search
    - move ordering has reduced move evaluation by 10 times just by putting attacks before
    - avoided the access (when possible on pointers) to direct members of classes
4.  **v0.1.0** first release package version
    - app class
    - command line arguments from `"f:m:n:vqhV"` (`./bin/echecs --help` to learn more)
    - released a compatibility mode for gnu++17 (c++17)
    - makefile does not use g++11 explicitely
    - github workflow for security checks
    - added signal handling and async input
    - minor improvement of the evaluation function
    - added basic endgame detection and alternate king map

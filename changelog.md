# Changelog

> "Lazyness is nothing more than the habit of resting before you get tired." - the Sole Survivor

1.  **v0.0.1** well... seems like I already did it
    *   port from previous repo in python
    *   better v classes so the computer can plan against the player
    *   did it in rust... am translating
    *   added some pre-defined class in lib to avoid making a whole new file just to avoid circular imports (because we include files and not features in cpp...)
    *   all files ready, no undefined references left
2.  **v0.0.2** improving AI
    *   finding bugs on copy is going to take a while
    *   valgrind is crying : millions of pieces are created and are not freed by the os... god dammit ubuntu
    *   added the ending string but it is not even standard notation (I called it FEN anyway)

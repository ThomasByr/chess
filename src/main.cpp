//! chess-cli
//!
//! Copyright (c) 2022, the chess-cli authors.
//! All rights reserved.
//!
//! Redistribution and use in source and binary forms, with or without
//! modification, are permitted provided that the following conditions are met:
//!
//! * Redistributions of source code must retain the above copyright notice,
//!   this list of conditions and the following disclaimer.
//!
//! * Redistributions in binary form must reproduce the above copyright notice,
//!   this list of conditions and the following disclaimer in the documentation
//!   and/or other materials provided with the distribution.
//!
//! * Neither the name of the chess-cli authors nor the names of its
//!   contributors may be used to endorse or promote products derived from
//!   this software without specific prior written permission.
//!
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//! POSSIBILITY OF SUCH DAMAGE.
//!
//! @file src/main.cpp
//! @author ThomasByr <https://github.com/ThomasByr>
//! @brief Main entry point for the chess-cli executable.
//!
//! @see <https://github.com/ThomasByr/chess>
//!
//! @param [in] -f, --fen      FEN [default:
//! "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"]
//! @param [in] -m, --moves    MOVES [default: ""]
//! @param [in] -n, --filename FILENAME [default: ""]
//! @param [in] -v, --verbose
//! @param [in] -q, --quiet
//! @param [in] -h, --help
//! @param [in] -V, --version
//!
//! @note -f, -m, -n are mutually exclusive and at the time of writing,
//!   not yet implemented.
//!
//! Move notation is as follows:
//!  - "e2e4" for a normal move
//!  - "O-O" or "O-O-O" for a castling move
//!  - "Nf3" for a pawn promotion (to a knight) (not yet implemented)
//!  - "best" to let the CPU choose the best move
//!  - "worst" to let the CPU choose the worst move
//!  - "rate" to rate the current position
//!  - "pass" to pass
//!  - "/quit" to quit the program
//!
//! @see <https://github.com/ThomasByr/chess>
//!

#include <iostream>

#include "lib.h"

#include "app.h"

int main(int argc, char *argv[]) {
    App app = App(argc, argv);
    // std::cout << app << std::endl;

    return app.run();
}

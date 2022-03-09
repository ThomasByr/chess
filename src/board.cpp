#include "board.h"

CastlingRights::CastlingRights() {
    kingside = true;
    queenside = true;
}

CastlingRights::~CastlingRights() {}

bool CastlingRights::can_kingside_castle() const { return kingside; }

bool CastlingRights::can_queenside_castle() const { return queenside; }

void CastlingRights::disable_kingside() { kingside = false; }

void CastlingRights::disable_queenside() { queenside = false; }

void CastlingRights::disable_all() {
    disable_kingside();
    disable_queenside();
}

void CastlingRights::enable_kingside() { kingside = true; }

void CastlingRights::enable_queenside() { queenside = true; }

void CastlingRights::enable_all() {
    enable_kingside();
    enable_queenside();
}

#pragma once

#include <iostream>
#include <string>

#include "lib.h"
#include "position.h"

class Piece {
  public:
    Piece(Color color, Position position);
    ~Piece();

    Color get_color() const;
    Position get_pos() const;

    void move_to(Position new_pos);

    virtual std::string get_name() const = 0;
    virtual int get_material_value() const = 0;
    virtual double get_weighted_value() const = 0;

    virtual bool is_starting_pawn() const = 0;
    virtual bool is_queenside_rook() const = 0;
    virtual bool is_kingside_rook() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Piece &piece);

  protected:
    Color color;
    Position position;
};

class Pawn : public Piece {
  public:
    Pawn(Color color, Position position);
    ~Pawn();

    std::string get_name() const;
    int get_material_value() const;
    double get_weighted_value() const;

    bool is_starting_pawn() const;
    bool is_queenside_rook() const;
    bool is_kingside_rook() const;

    friend std::ostream &operator<<(std::ostream &os, const Pawn &pawn);
};

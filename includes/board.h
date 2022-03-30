#pragma once

#include <iostream>
#include <string>
#include <tuple>

#include "lib.h"

#include "move.h"
#include "position.h"
#include "square.h"

class CastlingRights {
  public:
    /**
     * @brief Construct a new Castling Rights object
     *
     */
    CastlingRights();
    ~CastlingRights();

    /**
     * @brief if castling is possible for king side
     *
     * @return true - if castling is possible
     * @return false - otherwise
     */
    bool can_kingside_castle() const;
    /**
     * @brief if castling is possible for queen side
     *
     * @return true - if castling is possible
     * @return false - otherwise
     */
    bool can_queenside_castle() const;

    /**
     * @brief disables castling rights for king side
     *
     */
    void disable_kingside();
    /**
     * @brief disables castling rights for queen side
     *
     */
    void disable_queenside();
    /**
     * @brief disables castling rights for both sides
     *
     */
    void disable_all();

    /**
     * @brief enables castling rights for king side
     *
     */
    void enable_kingside();
    /**
     * @brief enables castling rights for queen side
     *
     */
    void enable_queenside();
    /**
     * @brief enables castling rights for both sides
     *
     */
    void enable_all();

  private:
    bool kingside;
    bool queenside;
};

class Board {
  public:
    /**
     * @brief Construct a new Board object
     *
     */
    Board();
    ~Board();

    /**
     * @brief setup the board with default values
     *
     * @return Board - new board
     */
    static Board new_board();

    CastlingRights *black_castling_rights; // black castling rights
    CastlingRights *white_castling_rights; // white castling rights

    /**
     * @brief evaluates the board for a given color
     *
     * @param ally_color ally color
     * @return double - evaluation value
     */
    double value_for(const Color &ally_color) const;
    /**
     * @brief Get the current player color object
     *
     * @return Color - enum class
     */
    Color get_current_player_color() const;

    /**
     * @brief apply a valid move to the board and return the new board
     *
     * @param move move to be applied
     * @return Board - new board
     */
    Board apply_eval_move(const Move &move);
    /**
     * @brief Get the legal moves object as a vector
     *
     * @return std::vector<Move> - vector of legal moves
     */
    std::vector<Move> get_legal_moves();

    std::tuple<Move, unsigned, double> get_next_best_move(int depth);
    std::tuple<Move, unsigned, double> get_next_worst_move(int depth);
    double minimax(int depth, double alpha, double beta, bool is_maximizing,
                   Color getting_move_for, unsigned board_count);

    /**
     * @brief Get the square object at a given position
     *
     * @param pos position of the square
     * @return Square - square
     */
    Square get_square(const Position &pos) const;
    /**
     * @brief replace a piece
     *
     * @param piece piece
     */
    void add_piece(Piece *piece);
    /**
     * @brief Get the piece object at a given position
     *
     * @param pos position of the piece
     * @return Piece* - piece
     */
    Piece *get_piece(const Position &pos);

    /**
     * @brief if the current board has an ally piece at a given position
     *
     * @param pos position
     * @param ally_color ally color
     * @return true - if there is an ally piece
     * @return false - otherwise
     */
    bool has_ally_piece(const Position &pos, const Color &ally_color);
    /**
     * @brief if the current board has an enemy piece at a given position
     *
     * @param pos position
     * @param ally_color ally color
     * @return true - if there is an enemy piece
     * @return false - otherwise
     */
    bool has_enemy_piece(const Position &pos, const Color &ally_color);
    /**
     * @brief if the current board has a piece at a given position
     *
     * @param pos position
     * @return true - if there is a piece
     * @return false - otherwise
     */
    bool has_piece(const Position &pos);
    /**
     * @brief if the current board has no piece at a given position
     *
     * @param pos position
     * @return true - if there is no piece
     * @return false - otherwise
     */
    bool has_no_piece(const Position &pos);

    /**
     * @brief Get the king position object
     * Might not be a valid position
     *
     * @param color color
     * @return Position - position
     */
    Position get_king_position(const Color &color) const;

    /**
     * @brief if a given position is threatened by a given color
     *
     * @param pos position
     * @param ally_color ally color
     * @return true - if the position is threatened
     * @return false - otherwise
     */
    bool is_threatened(const Position &pos, const Color &ally_color);
    /**
     * @brief if a given player is in check
     *
     * @param color color
     * @return true - if the player is in check
     * @return false - otherwise
     */
    bool is_in_check(const Color &color);

    /**
     * @brief moves a piece from one position to another
     *
     * @param from starting position
     * @param to ending position
     * @return Board - new board
     */
    Board move_piece(const Position &from, const Position &to);

    /**
     * @brief if a given player can castle kingside
     *
     * @param color color
     * @return true - if the player can castle kingside
     * @return false - otherwise
     */
    bool can_kingside_castle(const Color &color);
    /**
     * @brief if a given player can castle queenside
     *
     * @param color color
     * @return true - if the player can castle queenside
     * @return false - otherwise
     */
    bool can_queenside_castle(const Color &color);

    /**
     * @brief if a given player has sufficient material to checkmate
     *
     * @param color color
     * @return true - if the player has sufficient material
     * @return false - otherwise
     */
    bool has_sufficient_material(const Color &color) const;
    /**
     * @brief if a given player has insufficient material to ever checkmate
     *
     * @param color color
     * @return true - if the player has insufficient material
     * @return false - otherwise
     */
    bool has_insufficient_material(const Color &color) const;

    /**
     * @brief if the current board is a draw
     *
     * @return true - if the board is a draw
     * @return false - otherwise
     */
    bool is_stalemate();
    /**
     * @brief if the current game has ended with a checkmate
     *
     * @return true - if the game has ended
     * @return false - otherwise
     */
    bool is_checkmate();

    /**
     * @brief changes the current player color
     *
     * @return Board - board
     */
    Board change_turn();

    /**
     * @brief apply a move to the board and return the new board
     *
     * @param move move to be applied
     * @return Board - new board
     */
    Board apply_move(const Move &move);

    /**
     * @brief plays a valid more on the board
     *
     * @param move move to be applied
     * @return GameResult - result of the game w/ additional info
     */
    GameResult play_move(const Move &move);

    /**
     * @brief returns a rating bar for the current board
     *
     * @param len length of the bar
     * @return std::string - rating bar
     */
    std::string rating_bar(unsigned len);
    /**
     * @brief Get the turn color object
     *
     * @return Color - enum class
     */
    Color get_turn_color() const;
    /**
     * @brief Get the en passant object
     *
     * @return Position* - position
     */
    Position *get_en_passant() const;

    /**
     * @brief removes all pieces from the board for a given color
     *
     * @param color color
     * @return Board - new board
     */
    Board remove_all(const Color &color) const;
    /**
     * @brief makes all pieces of a given color queens
     *
     * @param color color
     * @return Board - new board
     */
    Board queen_all(const Color &color) const;

    /**
     * @brief Set the turn object to a given color
     *
     * @param color color
     * @return Board - new board
     */
    Board set_turn(const Color &color) const;

    /**
     * @brief returns the material advantage of a given player
     *
     * @param color color
     * @return int - material advantage
     */
    int get_material_advantage(const Color &color) const;

    /**
     * @brief if a move played by a given player is valid
     *
     * @param move move
     * @param player_color color
     * @return true - if the move is valid
     * @return false - otherwise
     */
    bool is_legal_move(const Move &move, const Color &player_color);

    /**
     * @brief fmt the board
     *
     * @param os ostream
     * @param board board
     * @return std::ostream& - ostream
     */
    friend std::ostream &operator<<(std::ostream &os, Board &board);

  private:
    Square squares[64];   // array of squares
    Position *en_passant; // en passant position
    Color turn;           // current turn color
};

class BoardBuilder {
  public:
    /**
     * @brief Construct a new Board Builder object
     * 
     */
    BoardBuilder();
    /**
     * @brief Construct a new Board Builder object
     * 
     * @param board board
     */
    BoardBuilder(const Board &board);
    ~BoardBuilder();

    /**
     * @brief places copies of a given piece on a row
     * 
     * @param piece piece
     * @return BoardBuilder - board builder
     */
    BoardBuilder row(const Piece &piece);
    /**
     * @brief places copies of a given piece on a column
     * 
     * @param piece piece
     * @return BoardBuilder - board builder
     */
    BoardBuilder column(const Piece &piece);

    /**
     * @brief adds a piece to the board by pointer
     * 
     * @param piece piece
     * @return BoardBuilder - board builder
     */
    BoardBuilder piece(Piece *piece);
    /**
     * @brief enables castling rights
     * 
     * @return BoardBuilder - board builder
     */
    BoardBuilder enable_castling();
    /**
     * @brief disables castling rights
     * 
     * @return BoardBuilder - board builder
     */
    BoardBuilder disable_castling();

    /**
     * @brief enables queen side castling rights for a given color
     * 
     * @param color color
     * @return BoardBuilder - board builder
     */
    BoardBuilder enable_queenside_castle(const Color &color);
    /**
     * @brief disables queen side castling rights for a given color
     * 
     * @param color color
     * @return BoardBuilder - board builder
     */
    BoardBuilder disable_queenside_castle(const Color &color);

    /**
     * @brief enables king side castling rights for a given color
     * 
     * @param color color
     * @return BoardBuilder - board builder
     */
    BoardBuilder enable_kingside_castle(const Color &color);
    /**
     * @brief disables king side castling rights for a given color
     * 
     * @param color color
     * @return BoardBuilder - board builder
     */
    BoardBuilder disable_kingside_castle(const Color &color);

    /**
     * @brief returns the board once the builder is finished
     * 
     * @return Board - the created
     */
    Board build() const;

  private:
    Board *board; // board
};

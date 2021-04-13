//
// Created by Harry Wright on 07/04/2021.
//
// The structures could be cleaned up a little
//

#ifndef SKAK_BOARD_H
#define SKAK_BOARD_H

#include "defs.h"
#include "stdlib.h"

#pragma mark - Type Defs

// File/Rank to square
#define FR2SQ(f, r) ((21 + (f)) + ((r)*10))
#define SQ64(sq120) (kSQ_120_TO_64[(sq120)])
#define SQ120(sq64) (kSQ_64_TO_120[(sq64)])

#define BOARD_MAX_LENGTH 120
#define STD_BOARD_LENGTH 64

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#pragma mark - Globals

// One with added checks to not allow invalid moves
//
// could maybe do this differently, with an array of diagonals but
// will get this working for now
extern int kSQ_120_TO_64[BOARD_MAX_LENGTH];
// This is the standard game board
extern int kSQ_64_TO_120[STD_BOARD_LENGTH];

extern int kFiles[BOARD_MAX_LENGTH];
extern int kRanks[BOARD_MAX_LENGTH];

#pragma mark - Enums

// Pieces
enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };

// Files
enum {
    FILE_A,
    FILE_B,
    FILE_C,
    FILE_D,
    FILE_E,
    FILE_F,
    FILE_G,
    FILE_H,
    FILE_NONE
};

// Ranks
enum {
    RANK_1,
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_NONE
};

// Colours
enum { WHITE, BLACK, BOTH };

// Just saves pointless writing
#define FILE(file, initial_value)                                         \
    A##file = initial_value, B##file, C##file, D##file, E##file, F##file, \
    G##file, H##file

// Board
enum {
    FILE(1, 21),
    FILE(2, 31),
    FILE(3, 41),
    FILE(4, 51),
    FILE(5, 61),
    FILE(6, 71),
    FILE(7, 81),
    FILE(8, 91), NO_SQ, OFF_BOARD
};

// Can castle
enum { wKC = 1, wQC = 2, bKC = 4, bQC = 8 };

#pragma mark - Structs

/**
 * Hold the moves played
 * */
typedef struct {
    int move;
    int castle_permission;
    int en_pas;
    int fifty_move;
    U64 position_hash;
} SKUndo;

/**
 * Structure to handle the board/game details
 * */
typedef struct {
    // The board structure
    int pieces[BOARD_MAX_LENGTH];

    // Where the pawns are on the board
    //
    // Helping with evaluation to help with passed/double pawns
    U64 pawns[3];

    // Where the kings are, helps with evaluation
    int king_square[2];

    // Side to move
    int side;

    // The square that can en passant
    int en_pas;

    // Counter for 50 move rule
    int fifty_move;

    // Half move counter
    int ply;
    int his_ply;

    // Can castling still be achieved
    //
    // White can caste king-side, black can castle queen-side is stored
    // as a 4 bit value, i.e 1 0 0 1
    int castle_permission;

    // Unique key for each position
    U64 position_hash;

    // These could be a struct maybe??
    // Number of pieces on the board
    //
    // These are for endgames, evaluations
    int piece_number[13];
    int juicers[2];  // Thanks for xQCow for this one
    int major_pieces[2];
    int minor_pieces[2];
    int material[2];

    // History of moves
    SKUndo history[MAX_GAME_MOVES];

    // piece list
    int piece_list[13][10];
} SKBoard;

#pragma mark - Functions

/**
 * Initialise a board
 * */
extern SKBoard *board_initialise(const char *fen);

/**
 * Create/Update a board from a fen
 * */
extern int board_make(const char *fen, SKBoard *pos);

/**
 *
 * */
extern void board_reset(SKBoard *pos);

/**
 *
 * */
extern int board_check(const SKBoard *pos);

/**
 *
 * */
extern void board_update(SKBoard *pos);

/**
 *
 * */
extern void board_print(const SKBoard *pos);

#endif  // SKAK_BOARD_H

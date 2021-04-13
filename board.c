//
// Created by Harry Wright on 07/04/2021.
//

#include "board.h"

#include "assert.h"
#include "bitboards.h"
#include "board+private.h"
#include "hash.h"
#include "pieces.h"

#pragma mark - Globals/Define

#define CASE(q, statement) \
    case q:                \
        statement;         \
        break;

#define COUNT_CASE \
    case '1':      \
    case '2':      \
    case '3':      \
    case '4':      \
    case '5':      \
    case '6':      \
    case '7':      \
    case '8':

#define SLASH_CASE \
    case '/':      \
    case ' ':

#pragma mark - Globals/Variables

int kSQ_120_TO_64[BOARD_MAX_LENGTH];
int kSQ_64_TO_120[STD_BOARD_LENGTH];

int kFiles[BOARD_MAX_LENGTH];
int kRanks[BOARD_MAX_LENGTH];

#pragma mark - Functions

void board_init() {
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0;

    for (index = 0; index < BOARD_MAX_LENGTH; ++index) {
        kSQ_120_TO_64[index] = 65;

        kFiles[index] = OFF_BOARD;
        kRanks[index] = OFF_BOARD;
    }

    for (index = 0; index < 64; ++index) {
        kSQ_64_TO_120[index] = 120;
    }

    for (rank = RANK_1; rank <= RANK_8; ++rank) {
        for (file = FILE_A; file <= FILE_H; ++file) {
            sq = FR2SQ(file, rank);
            kFiles[sq] = file;
            kRanks[sq] = rank;

            kSQ_64_TO_120[sq64] = sq;
            kSQ_120_TO_64[sq] = sq64;
            sq64++;
        }
    }
}

void board_reset(SKBoard *pos) {
    for (int i = 0; i < BOARD_MAX_LENGTH; ++i) {
        pos->pieces[i] = OFF_BOARD;
    }

    for (int i = 0; i < 64; ++i) {
        pos->pieces[SQ120(i)] = EMPTY;
    }

    for (int i = 0; i < 2; ++i) {
        pos->juicers[i] = 0;
        pos->major_pieces[i] = 0;
        pos->minor_pieces[i] = 0;
        pos->material[i] = 0;
    }

    for (int i = 0; i < 3; ++i) {
        pos->pawns[i] = 0ULL;
    }

    for (int i = 0; i < 13; ++i) {
        pos->piece_number[i] = 0;
    }

    pos->king_square[WHITE] = pos->king_square[BLACK] = NO_SQ;

    pos->side = BOTH;
    pos->en_pas = NO_SQ;
    pos->fifty_move = 0;

    pos->ply = 0;
    pos->his_ply = 0;

    pos->castle_permission = 0;

    pos->position_hash = 0ULL;
}

#define PIECES_FOR_SQ(_sq, _pos) _pos->pieces[SQ120(_sq)]

#define COUNT_CHECK(_pawns, _color, _pos)                                      \
    int _color##_count = count_bits(_pawns[_color]);                           \
    ASSERT(_color##_count ==                                                   \
           (_color == BOTH ? (_pos->piece_number[bP] + _pos->piece_number[wP]) \
                           : _pos->piece_number[_color == WHITE ? wP : bP]));

#define BITBOARD_CHECK(_pawns, _color, _pos)                          \
    while (_pawns[_color]) {                                          \
        int sq64 = pop_bit(&_pawns[_color]);                          \
        ASSERT(_color == BOTH ? ((PIECES_FOR_SQ(sq64, _pos) == bP) || \
                                 (PIECES_FOR_SQ(sq64, _pos) == wP))   \
                              : PIECES_FOR_SQ(sq64, _pos) ==          \
                                    (_color == WHITE ? wP : bP));     \
    }

#define COLORED_CHECK(__var, __color, __pos) \
    __var[__color] == __pos->__var[__color]

#define VAR_CHECKER(__var, __pos) \
    (COLORED_CHECK(__var, WHITE, __pos)) && (COLORED_CHECK(__var, BLACK, __pos))

int board_check(const SKBoard *pos) {
    int piece_number[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int juicers[2] = {0, 0};
    int major_pieces[2] = {0, 0};
    int minor_pieces[2] = {0, 0};
    int material[2] = {0, 0};

    U64 pawns[3] = {0ULL, 0ULL, 0ULL};

    pawns[WHITE] = pos->pawns[WHITE];
    pawns[BLACK] = pos->pawns[BLACK];
    pawns[BOTH] = pos->pawns[BOTH];

    // Check piece list
    for (int i = wP; i <= bK; ++i) {
        for (int j = 0; j < pos->piece_number[i]; ++j) {
            int sq = pos->piece_list[i][j];
            ASSERT(pos->pieces[sq] == i);
        }
    }

    for (int sq64 = 0; sq64 < 64; ++sq64) {
        int sq120 = SQ120(sq64);

        int piece = pos->pieces[sq120];
        piece_number[piece]++;

        int color = kPieceColor[piece];
        if (kPieceBig[piece] == TRUE) juicers[color]++;
        if (kPieceMin[piece] == TRUE) minor_pieces[color]++;
        if (kPieceMaj[piece] == TRUE) major_pieces[color]++;

        material[color] += kPieceValue[piece];
    }

    for (int i = wP; i < bK; ++i) {
        ASSERT(piece_number[i] == pos->piece_number[i]);
    }

    COUNT_CHECK(pawns, WHITE, pos);
    COUNT_CHECK(pawns, BLACK, pos);
    COUNT_CHECK(pawns, BOTH, pos);

    BITBOARD_CHECK(pawns, WHITE, pos);
    BITBOARD_CHECK(pawns, BLACK, pos);
    BITBOARD_CHECK(pawns, BOTH, pos);

    ASSERT(VAR_CHECKER(material, pos));
    ASSERT(VAR_CHECKER(major_pieces, pos));
    ASSERT(VAR_CHECKER(minor_pieces, pos));
    ASSERT(VAR_CHECKER(juicers, pos));

    ASSERT(pos->side == WHITE || pos->side == BLACK);
    ASSERT(hash_key_make(pos) == pos->position_hash);

    ASSERT(pos->en_pas == NO_SQ ||
           (kRanks[pos->en_pas] == RANK_6 && pos->side == WHITE) ||
           (kRanks[pos->en_pas] == RANK_3 && pos->side == BLACK));

    ASSERT(pos->pieces[pos->king_square[WHITE]] == wK);
    ASSERT(pos->pieces[pos->king_square[BLACK]] == bK);

    return TRUE;
}

void board_update(SKBoard *pos) {
    int piece, color;
    for (int sq = 0; sq < BOARD_MAX_LENGTH; ++sq) {
        piece = pos->pieces[sq];
        if (piece != OFF_BOARD && piece != EMPTY) {
            color = kPieceColor[piece];
            if (kPieceBig[piece] == TRUE) pos->juicers[color]++;
            if (kPieceMaj[piece] == TRUE) pos->major_pieces[color]++;
            if (kPieceMin[piece] == TRUE) pos->minor_pieces[color]++;

            pos->material[color] += kPieceValue[piece];

            pos->piece_list[piece][pos->piece_number[piece]] = sq;
            pos->piece_number[piece]++;

            if (piece == wK) pos->king_square[WHITE] = sq;
            if (piece == bK) pos->king_square[BLACK] = sq;

            if (piece == wP) {
                set_bit(&pos->pawns[WHITE], SQ64(sq));
                set_bit(&pos->pawns[BOTH], SQ64(sq));
            } else if (piece == bP) {
                set_bit(&pos->pawns[BLACK], SQ64(sq));
                set_bit(&pos->pawns[BOTH], SQ64(sq));
            }
        }
    }
}

SKBoard *board_initialise(const char *fen) {
    SKBoard *board = malloc(sizeof(&board));

    if (fen != NULL) {
        board_make(fen, board);
    }

    return board;
}

int board_make(const char *fen, SKBoard *pos) {
    ASSERT(fen != NULL)
    ASSERT(pos != NULL)

    int rank = RANK_8;
    int file = FILE_A;
    int piece = 0;
    int count = 0;
    int sq64 = 0;
    int sq120 = 0;

    board_reset(pos);

    while (rank >= RANK_1 && *fen) {
        count = 1;
        switch (*fen) {
            CASE('p', piece = bP)
            CASE('r', piece = bR)
            CASE('n', piece = bN)
            CASE('b', piece = bB)
            CASE('k', piece = bK)
            CASE('q', piece = bQ)
            CASE('P', piece = wP)
            CASE('R', piece = wR)
            CASE('N', piece = wN)
            CASE('B', piece = wB)
            CASE('K', piece = wK)
            CASE('Q', piece = wQ)

            COUNT_CASE
            piece = EMPTY;
            count = *fen - '0';
            break;

            SLASH_CASE
            rank--;
            file = FILE_A;
            fen++;
            continue;

            default:
                SKLog("FEN error: \n");
                return -1;
        }

        // loop around the numbers set in FEN
        for (int i = 0; i < count; ++i) {
            sq64 = rank * 8 + file;
            sq120 = SQ120(sq64);

            if (piece != EMPTY) {
                pos->pieces[sq120] = piece;
            }

            file++;
        }

        fen++;
    }

    // Set side to move
    ASSERT(*fen == 'w' || *fen == 'b')
    pos->side = (*fen == 'w') ? WHITE : BLACK;
    fen += 2;

    // Castling permission
    for (int i = 0; i < 4; ++i) {
        if (*fen == ' ') {
            break;
        }

        switch (*fen) {
            CASE('K', pos->castle_permission |= wKC)
            CASE('Q', pos->castle_permission |= wQC)
            CASE('k', pos->castle_permission |= bKC)
            CASE('q', pos->castle_permission |= bQC)
            default:
                break;
        }

        fen++;
    }

    // Check it's right
    ASSERT(pos->castle_permission >= 0 && pos->castle_permission <= 15)
    fen++;

    if (*fen != '-') {
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        ASSERT(file >= FILE_A && file <= FILE_H);
        ASSERT(rank >= RANK_1 && rank <= RANK_8);

        pos->en_pas = FR2SQ(file, rank);
    }

    pos->position_hash = hash_key_make(pos);

    board_update(pos);

    return 0;
}

void board_print(const SKBoard *pos) {
    SKLog("\nBoard:\n\n");
    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        SKLog("%d", rank + 1);
        for (int file = FILE_A; file <= FILE_H; file++) {
            int sq = FR2SQ(file, rank);
            int piece = pos->pieces[sq];
            SKLog("%3c", kPieceChar[piece]);
        }
        SKLogLine;
    }

    SKLog(" ");
    for (int i = FILE_A; i <= FILE_H; i++) {
        SKLog("%3c", 'a' + i);
    }
    SKLogLine;

    SKLogLine;
    SKLog("Side to move: %c\n", kSideChar[pos->side]);
    SKDebugLog("En Passant %d\n", pos->en_pas);
    SKDebugLog("Castling: %c%c%c%c\n", pos->castle_permission & wKC ? 'K' : '-',
               pos->castle_permission & wQC ? 'Q' : '-',
               pos->castle_permission & bKC ? 'k' : '-',
               pos->castle_permission & bQC ? 'q' : '-');
    SKDebugLog("Position Hash: %11llX\n", pos->position_hash);
}

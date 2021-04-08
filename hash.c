//
// Created by Harry Wright on 08/04/2021.
//

#include "hash.h"

#include "stdlib.h"
#include "hash+private.h"
#include "assert.h"

#define RAND_64                                                \
    ((U64)rand() + ((U64)rand() << 15) + ((U64)rand() << 30) + \
     ((U64)rand() << 45) + (((U64)rand() & 0xf) << 60));

U64 kSideKey;
U64 kCastleKeys[16];
U64 kPieceKeys[13][120];

void hash_keys_init() {
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 120; ++j) {
            // NOLINTNEXTLINE
            kPieceKeys[i][j] = RAND_64;
        }
    }

    // NOLINTNEXTLINE
    kSideKey = RAND_64;

    for (int i = 0; i < 16; ++i) {
        // NOLINTNEXTLINE
        kCastleKeys[i] = RAND_64;
    }
}

U64 hash_key_make(SKBoard *pos) {
    U64 key = 0;
    int piece = EMPTY;

    for (int i = 0; i < BOARD_MAX_LENGTH; ++i) {
        piece = pos->piece_number[i];
        if (piece != NO_SQ && piece != EMPTY) {
            ASSERT(piece >= wP && piece <= bK)
            key ^= kPieceKeys[piece][i];
        }
    }

    if (pos->side == WHITE) {
        key ^= kSideKey;
    }

    if (pos->en_pas != NO_SQ) {
        ASSERT(pos->en_pas >= 0 && pos->en_pas < BOARD_MAX_LENGTH)
        key ^= kPieceKeys[EMPTY][pos->en_pas];
    }

    ASSERT(pos->castle_permission >= 0 && pos->castle_permission <= 15)
    key ^= kCastleKeys[pos->castle_permission];

    return key;
}

//
// Created by Harry Wright on 08/04/2021.
//

#ifndef SKAK_HASH_H
#define SKAK_HASH_H

#include "defs.h"

#include "board.h"

extern U64 KSideKey;
extern U64 kCastleKeys[16];
extern U64 kPieceKeys[13][120];

/**
 * Generate a hash key for the current position
 * */
extern U64 hash_key_make(SKBoard *pos);

#endif  // SKAK_HASH_H

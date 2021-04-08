//
// Created by Harry Wright on 07/04/2021.
//

#ifndef SKAK_BITBOARDS_H
#define SKAK_BITBOARDS_H

#include "defs.h"

#pragma mark - Define

#define POP(bb) pop_bit(bb)
#define COUNT(bb) count_bits(bb)
#define PRINT(bb) print(bb)

#pragma mark - Globals

extern U64 kSetMask[64];
extern U64 kClearMask[64];

#pragma mark - Inline function

/**
 * Set a bit at a required square
 *
 * @param bb The bitboard
 * @param sq Pretty self explanatory this one lads
 * */
static inline void set_bit(U64 *bb, int sq) { ((*bb) |= kSetMask[(sq)]); }

/**
 * Clear a bit at a required square
 *
 * @param bb The bitboard
 * @param sq Pretty self explanatory this one lads
 * */
static inline void clear_bit(U64 *bb, int sq) { ((*bb) &= kClearMask[(sq)]); }

#pragma mark - Function

/**
 * Pop the last bit from the bitboard
 *
 * @note This is from https://www.chessprogramming.org/Looking_for_Magics
 * @param bb - The bitboard
 * */
extern int pop_bit(U64 *bb);

/**
 * Count the amount of pawns on the board
 *
 * @note This is from https://www.chessprogramming.org/Looking_for_Magics
 * @param b - The bitboard
 * */
extern int count_bits(U64 b);

/**
 * Print out the pawn bitboard
 *
 * @note This is more for debug
 * @param bb - The bitboard
 * */
extern void print_bit(U64 bb);

#endif  // SKAK_BITBOARDS_H

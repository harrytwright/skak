//
// Created by Harry Wright on 07/04/2021.
//

#ifndef SKAK_BITBOARDS_H
#define SKAK_BITBOARDS_H

#include "defs.h"

#pragma mark - Type Defs

#define POP(bb) pop_bit(bb)
#define COUNT(bb) count_bits(bb)
#define PRINT(bb) print(bb)

#pragma mark - Function

/**
 * Please use POP()
 * */
extern int pop_bit(U64 *bb);

/**
 * Please use COUNT()
 * */
extern int count_bits(U64 b);

/**
 * Please use PRINT()
 * */
extern void print(U64 bb);

#endif  // SKAK_BITBOARDS_H

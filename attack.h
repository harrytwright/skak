//
// Created by Harry Wright on 13/04/2021.
//

#ifndef SKAK_ATTACK_H
#define SKAK_ATTACK_H

#include "board.h"

#define IsBQ(p) (kPieceBishopQueen[(p)])
#define IsRQ(p) (kPieceRookQueen[(p)])
#define IsKn(p) (kPieceKnight[(p)])
#define IsKi(p) (kPieceKing[(p)])

extern int kPieceKnight[13];
extern int kPieceKing[13];
extern int kPieceRookQueen[13];
extern int kPieceBishopQueen[13];

extern const int kKnightDirection[8];
extern const int kRookDirection[4];
extern const int kBishopDirection[4];
extern const int kKingDirection[8];

int square_attacked(int sq, int side, const SKBoard *pos);

#endif  // SKAK_ATTACK_H

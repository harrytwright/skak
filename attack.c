//
// Created by Harry Wright on 13/04/2021.
//

#include "attack.h"

#include "defs.h"
#include "pieces.h"

const int kKnightDirection[8] = {-8, -19, -21, -12, 8, 19, 21, 12};
const int kRookDirection[4] = {-1, -10, 1, 10};
const int kBishopDirection[4] = {-9, -11, 11, 9};
const int kKingDirection[8] = {-1, -10, 1, 10, -9, -11, 11, 9};

int kPieceKnight[13] = { FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE };
int kPieceKing[13] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE };
int kPieceRookQueen[13] = { FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE };
int kPieceBishopQueen[13] = { FALSE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE };

int square_attacked(const int sq, const int side, const SKBoard *pos) {
    int pce,index,t_sq,dir;

    // pawns
    if(side == WHITE) {
        if(pos->pieces[sq-11] == wP || pos->pieces[sq-9] == wP) {
            return TRUE;
        }
    } else {
        if(pos->pieces[sq+11] == bP || pos->pieces[sq+9] == bP) {
            return TRUE;
        }
    }

    // knights
    for(index = 0; index < 8; ++index) {
        pce = pos->pieces[sq + kKnightDirection[index]];
        if(pce != OFF_BOARD && pce != EMPTY && IsKn(pce) && kPieceColor[pce]==side) {
            return TRUE;
        }
    }

    // rooks, queens
    for(index = 0; index < 4; ++index) {
        dir = kRookDirection[index];
        t_sq = sq + dir;
        pce = pos->pieces[t_sq];
        while(pce != OFF_BOARD) {
            if(pce != EMPTY) {
                if(IsRQ(pce) && kPieceColor[pce] == side) {
                    return TRUE;
                }
                break;
            }
            t_sq += dir;
            pce = pos->pieces[t_sq];
        }
    }

    // bishops, queens
    for(index = 0; index < 4; ++index) {
        dir = kBishopDirection[index];
        t_sq = sq + dir;
        pce = pos->pieces[t_sq];
        while(pce != OFF_BOARD) {
            if(pce != EMPTY) {
                if(IsBQ(pce) && kPieceColor[pce] == side) {
                    return TRUE;
                }
                break;
            }
            t_sq += dir;
            pce = pos->pieces[t_sq];
        }
    }

    // kings
    for(index = 0; index < 8; ++index) {
        pce = pos->pieces[sq + kKingDirection[index]];
        if(pce != OFF_BOARD && pce != EMPTY && IsKi(pce) && kPieceColor[pce]==side) {
            return TRUE;
        }
    }

    return FALSE;
}
//
// Created by Harry Wright on 13/04/2021.
//

#include "pieces.h"

#include "board.h"
#include "defs.h"

char kPieceChar[] = ".PNBRQKpnbrqk";
char kSideChar[] = "wb-";
char kRankChar[] = "12345678";
char kFileChar[] = "abcdefgh";

int kPieceBig[13] = {FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE,
                     FALSE, TRUE,  TRUE, TRUE, TRUE, TRUE};
int kPieceMaj[13] = {FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE,
                     FALSE, FALSE, FALSE, TRUE,  TRUE, TRUE};
int kPieceMin[13] = {FALSE, FALSE, TRUE, TRUE,  FALSE, FALSE, FALSE,
                     FALSE, TRUE,  TRUE, FALSE, FALSE, FALSE};
int kPieceColor[13] = { BOTH, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
                        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK };

int kPieceValue[13] = {0,   100, 325, 325, 550,  1000, 50000,
                       100, 325, 325, 550, 1000, 50000};
//
// Created by Harry Wright on 07/04/2021.
//

#include "bitboards.h"
#include "board.h"

void print(U64 bb) {
    U64 board = 1ULL;

    int rank = 0;
    int file = 0;
    int sq = 0;
    int sq64 = 0;

    SKLogLine;
    for (rank = RANK_8; rank >= RANK_1; --rank) {
        SKLog("%d\t", rank+1);
        for (file = FILE_A; file <= FILE_H; ++file) {
            sq = FR2SQ(file, rank);
            sq64 = SQ64(sq);

            if ((board << sq64) & bb) {
                SKLog("X ");
            } else {
                SKLog("- ");
            }
        }
        SKLogLine;
    }
    SKLog("\tA B C D E F G H");
    SKLogLine;
}

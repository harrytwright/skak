//
// Created by Harry Wright on 07/04/2021.
//

#include "assert.h"
#include "attack.h"
#include "bitboards.h"
#include "board.h"
#include "defs.h"
#include "hash.h"
#include "init.h"
#include "pieces.h"
#include "stdio.h"
#include "stdlib.h"

#define RANDOM_FEN_1 "7k/P7/PpK4P/2p3NN/2R3q1/PP6/3p3P/n7 w - - 0 1"
#define RANDOM_FEN_2 "rQ5R/4B3/1nb3r1/1B6/P3k1N1/q2R4/NbP1K1Pn/3Q4 w - - 0 1"
#define FEN4 \
    "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

//void showAttack(const int side, const SKBoard *pos) {
//    SKLogLine;
//    for (int i = RANK_8; i >= RANK_1; --i) {
//        for (int j = FILE_A; j <= FILE_H; ++j) {
//            int sq = FR2SQ(j, i);
//            if (square_attacked(sq, side, pos) == TRUE) {
//                SKLog(" X ");
//            } else {
//                SKLog(" - ");
//            }
//        }
//        SKLogLine;
//    }
//    SKLogLine;
//    SKLogLine;
//}

int main() {
    initialise();

//    SKBoard board[1];
////    board_make("8/3q4/8/8/4Q3/8/8/8 w - - 0 2", board);
//        board_make(RANDOM_FEN_1, board);
//    board_print(board);
//    //    ASSERT(board_check(board) == TRUE);
//
//    SKLogLine;
//    SKLogLine;
//
//    SKLog("White Attacking: \n");
//    showAttack(WHITE, board);
//
//    SKLogLine;
//    SKLogLine;
//    SKLog("Black Attacking: \n");
//    showAttack(BLACK, board);
    //    board->piece_number[wP]--;
    //    ASSERT(board_check(board) == TRUE);

    //    print_bit(board->pawns[WHITE]);
    //    print_bit(board->pawns[BLACK]);
    //    print_bit(board->pawns[BOTH]);
    //

    //    SKLog("=> Files\n");
    //    for (int i = 0; i < BOARD_MAX_LENGTH; ++i) {
    //        if (i % 10 == 0 && i != 0) SKLogLine;
    //        SKLog("%4d", kFiles[i]);
    //    }
    //
    //    SKLogLine;
    //    SKLogLine;
    //
    //    SKLog("=> Ranks\n");
    //    for (int i = 0; i < BOARD_MAX_LENGTH; ++i) {
    //        if (i % 10 == 0 && i != 0) SKLogLine;
    //        SKLog("%4d", kRanks[i]);
    //    }

    //    SKBoard board[1];
    //
    //    board_make(START_FEN, board);
    //    board_print(board);
    //
    //    board_make(RANDOM_FEN_1, board);
    //    board_print(board);
    //
    //    board_make(RANDOM_FEN_2, board);
    //    board_print(board);

    return 0;
}

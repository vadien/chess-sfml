#pragma once
#include "BoardDisplay.hpp"
class Move {
  int startSquare;
  int targetSquare;

public:
  static void forcedMove(BoardDisplay &board, int startSquare, int endSquare) {
    // Any piece will currently 'take' any other piece.
    int i = board.pieces[startSquare];
    board.pieces[endSquare] = i;
    if (startSquare != endSquare) {
      board.pieces[startSquare] = 0;
    }
    std::cout << "Forced move: sq " << startSquare << " to sq " << endSquare
              << std::endl;
    std::cout << "startSquare should be " << board.pieces[startSquare]
              << ", endSquare should be " << board.pieces[endSquare]
              << std::endl;
    std::cout << "startSquare is now " << board.getPieces()[startSquare]
              << ", endSquare is now " << board.getPieces()[endSquare]
              << std::endl;
  }
  void checkIsLegalMove(int startSquare, int targetSquare) {}
};

#pragma once

class Piece {
  int startingSquare;
  int currentSquare;
  bool isDraggable;

public:
  static const short EMPTY = 0;
  static const short PAWN = 1;
  static const short KNIGHT = 2;
  static const short BISHOP = 3;
  static const short ROOK = 4;
  static const short QUEEN = 5;
  static const short KING = 6;

  static const short WHITE = 8;
  static const short BLACK = 16;
};

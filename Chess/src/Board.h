#pragma once

#include "Piece.h"

#include <iostream>

class Board{

public:
	Piece* pieces[8 * 8];

	Board();
	Piece* getPiece(char col, int row) const;
	void setPiece(Piece* piece, char col, int row);


};
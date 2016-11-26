#pragma once

#include "Piece.h"

struct EnPassantStruct {

public:

	char colPos;
	int rowPos;

	EnPassantStruct(char colPos, int rowPos) : colPos(colPos), rowPos(rowPos) { }

};

class GameController {

public:
	static EnPassantStruct* enPassant;

};
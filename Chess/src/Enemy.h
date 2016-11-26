#pragma once

#include "Board.h"
#include "Piece.h"
#include "GameController.h"

class Enemy {

private:
	bool verifPieceOntheWay(const Board& board, Piece piece, char colActualPos, int rowActualPos, char colTargetPos, int rowTargetPos);
	bool verifCastling(const Board& board, char colActualPos, int rowActualPos, char colTargetPos, int rowTargetPos, bool& castlingLeft, bool& castlingRight);
	void verifEnpassant(char colActualPos, int rowActualPos, char colTargetPos, int rowTargetPos, bool& movimentoEnPassant);

public:
	bool makeMovement(Board& board, Piece piece, char colActualPos, int rowActualPos, char colTargetPos, int rowTargetPos);
	bool selecPieceVerif(Board board, char col, int row);
	bool selecDestiVerif(Board board, char col, int row);

};
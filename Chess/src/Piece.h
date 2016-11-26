#pragma once

#include <iostream>

enum Color {WHITE, BLACK};
enum Type {PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING};

class Piece{

public:
	Color color;
	Type type;
	bool neverMoved;

	Piece(Color color, Type type, bool neverMoved = true)  : color(color), type(type), neverMoved(neverMoved){}

	bool canMakeaMovementPlayer(const char colActualPos, const int rowActualPos, const char colTargetPos, const int rowTargetPos, Type type);
	bool canMakeaMovementEnemy(const char colActualPos, const int rowActualPos, const char colTargetPos, const int rowTargetPos, Type type);

};
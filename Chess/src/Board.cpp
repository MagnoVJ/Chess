#include "Board.h"

Board::Board(){

	for(int i = 0; i < 8 * 8; i++)
		pieces[i] = nullptr;

	//Preenche os peoes brancos
	for(int x = 0; x < 8; x++)
		pieces[x + 1 * 8] = new Piece(WHITE, PAWN);

	//Preenche os dois cavalos brancos
	pieces[1 + 0 * 8] = new Piece(WHITE, KNIGHT);
	pieces[6 + 0 * 8] = new Piece(WHITE, KNIGHT);

	//Preenche os dois bisbos brancos
	pieces[2 + 0 * 8] = new Piece(WHITE, BISHOP);
	pieces[5 + 0 * 8] = new Piece(WHITE, BISHOP);

	//Preenche as duas torres brancas
	pieces[0 + 0 * 8] = new Piece(WHITE, ROOK);
	pieces[7 + 0 * 8] = new Piece(WHITE, ROOK);

	//Preenche a rainha branca
	pieces[3 + 0 * 8] = new Piece(WHITE, QUEEN);
	 
	//Preenche o rei branco
	pieces[4 + 0 * 8] = new Piece(WHITE, KING);

	//Preenche os peoes pretos
	for(int x = 0; x < 8; x++)
		pieces[x + 6 * 8] = new Piece(BLACK, PAWN);

	//Preenche os dois cavalos pretos
	pieces[1 + 7 * 8] = new Piece(BLACK, KNIGHT);
	pieces[6 + 7 * 8] = new Piece(BLACK, KNIGHT);

	//Preenche os dois bisbos pretos
	pieces[2 + 7 * 8] = new Piece(BLACK, BISHOP);
	pieces[5 + 7 * 8] = new Piece(BLACK, BISHOP);

	//Preenche as duas torres pretas
	pieces[0 + 7 * 8] = new Piece(BLACK, ROOK);
	pieces[7 + 7 * 8] = new Piece(BLACK, ROOK);

	//Preenche a rainha preta
	pieces[3 + 7 * 8] = new Piece(BLACK, QUEEN);

	//Preenche o rei preto
	pieces[4 + 7 * 8] = new Piece(BLACK, KING);

}

Piece* Board::getPiece(char col, int row) const{ 

	int x, y;
	
	if(row < 1 || row > 8){
		std::cout << "ERRO::Board::getPiece:: row not valid" << std::endl;
		return nullptr;
	}

	y = row - 1;

	if(col == 'A' || col == 'B' || col == 'C' ||
	   col == 'D' || col == 'E' || col == 'F' ||
	   col == 'G' || col == 'H')
	   x = col - 65;
	else if(col == 'a' || col == 'b' || col == 'c' ||
	   col == 'd' || col == 'e' || col == 'f' ||
	   col == 'g' || col == 'h')
	   x = col - 97;
	else{
		std::cout << "ERRO::Board::getPiece:: col not valid" << std::endl;
		return nullptr;
	}

	return pieces[x + y * 8];

}

void Board::setPiece(Piece* piece, char col, int row){

	int x, y;

	if(row < 1 || row > 8){
		std::cout << "ERRO::Board::setPiece:: row not valid" << std::endl;
		return;
	}

	y = row - 1;

	if(col == 'A' || col == 'B' || col == 'C' ||
	   col == 'D' || col == 'E' || col == 'F' ||
	   col == 'G' || col == 'H')
	   x = col - 65;
	else if(col == 'a' || col == 'b' || col == 'c' ||
	   col == 'd' || col == 'e' || col == 'f' ||
	   col == 'g' || col == 'h')
	   x = col - 97;
	else{
		std::cout << "ERRO::Board:::setPiece:: col not valid" << std::endl;
		return;
	}

	pieces[x + y * 8] = piece;

}

#include "src/Board.h"
#include "src/Player.h"
#include "src/Enemy.h"

#include <iostream>
#include <string>
#include <ctype.h>

enum Turno {WHITE_TURNO, BLACK_TURNO};

#pragma region "Test functions"
void drawBoard();
void playerJogada();
void enemyJogada();
#pragma endregion

Board board;
Player player;
Enemy enemy;


Turno turno;
bool done;

int main(){

	turno = WHITE_TURNO;
	done = false;

	drawBoard();

	while(!done){

		if(turno == WHITE_TURNO)
			playerJogada();

		drawBoard();

		if(turno == BLACK_TURNO)
			enemyJogada();

		drawBoard();

	}

	getchar();

}

void drawBoard(){

	for(int y = 7; y >= 0; y--){

		if(y == 7){
			char topDesc = 'a';
			std::cout << "    ";
			for(int cont = 1; cont <= 8; cont++){
				std::cout << topDesc << "   ";
				topDesc++;
			}
			std::cout << std::endl << std::endl;
		}

		std::cout << y + 1 << "   ";

		for(int x = 0; x < 8; x++){

			if(board.pieces[x + y * 8] == nullptr)
				std::cout << "--  ";

			else if(board.pieces[x + y * 8]->color == WHITE){
				if(board.pieces[x + y * 8]->type == PAWN)
					std::cout << "WP  ";
				else if(board.pieces[x + y * 8]->type == KNIGHT)
					std::cout << "WN  ";
				else if(board.pieces[x + y * 8]->type == BISHOP)
					std::cout << "WB  ";
				else if(board.pieces[x + y * 8]->type == ROOK)
					std::cout << "WR  ";
				else if(board.pieces[x + y * 8]->type == QUEEN)
					std::cout << "WQ  ";
				else if(board.pieces[x + y * 8]->type == KING)
					std::cout << "WK  ";
			}

			else if(board.pieces[x + y * 8]->color == BLACK){
				if(board.pieces[x + y * 8]->type == PAWN)
					std::cout << "BP  ";
				else if(board.pieces[x + y * 8]->type == KNIGHT)
					std::cout << "BN  ";
				else if(board.pieces[x + y * 8]->type == BISHOP)
					std::cout << "BB  ";
				else if(board.pieces[x + y * 8]->type == ROOK)
					std::cout << "BR  ";
				else if(board.pieces[x + y * 8]->type == QUEEN)
					std::cout << "BQ  ";
				else if(board.pieces[x + y * 8]->type == KING)
					std::cout << "BK  ";
			}

		}
		std::cout << " "<< y + 1;
		std::cout << std::endl << std::endl;

	}

	char topDesc = 'a';
	std::cout << "    ";
	for(int cont = 1; cont <= 8; cont++){
		std::cout << topDesc << "   ";
		topDesc++;
	}

}

//Perguntar por uma col e um row para selecionar a peca
//Se for inválido retorna falso
//Se for verdadeiro entre em um loop para obter o destino
//Se o destino for válido retorna true se for inválido retorna o loop pedindo pelo destino
void playerJogada(){

	std::string coordsSelect;
	std::string coordsTarget;

	bool done = false;
	char col;
	int row;

	while(!done){

		std::cout << std::endl << std::endl <<"Selecione a coordenada da peca a ser movida: ";
		std::getline(std::cin, coordsSelect);

		col = coordsSelect[0];
		row = (int)coordsSelect[1] - 48;

		//Verifica se a peca é valida
		if(!player.selecPieceVerif(board, col, row))
			std::cout << std::endl << "ERROR::playerJogada::player.selecPieceVerif:: a peca selecionada nao e valida" << std::endl;
		//Se for válida prossiga...
		else{

			std::cout << "Selecione a coordenada de destino da peca: ";
			std::getline(std::cin, coordsTarget);

			col = coordsTarget[0];
			row = (int)coordsTarget[1] - 48;

			//Verifica se o destino é valido
			if(!player.selecDestiVerif(board, col, row))
				std::cout << std::endl <<"ERROR::playerJogada::player.selecDestiVerif:: o destino selecionado nao e valida" << std::endl;
			//Se for válido prossiga...
			else{
				//Obtem as posicoes de selecao e de destino
				char colActualPos = tolower(coordsSelect[0]);
				int rowActualPos = (int)coordsSelect[1] - 48;
				char colTargetPos = tolower(coordsTarget[0]);
				int rowTargetPos = (int)coordsTarget[1] - 48;

				const Piece* piece = board.getPiece(colActualPos, rowActualPos);

				//So para ter certeza se o piece foi retornado corretamente
				if(piece == nullptr)
					std::cout << "O ou... ERROR::Main::playerJogada:: linha aprox 155 piece == nullptr" << std::endl;
				else{
					if(!player.makeMovement(board, *piece, colActualPos, rowActualPos, colTargetPos, rowTargetPos))
						std::cout << "ERROR::Main::playerJogada::makeMovement:: movimento nao e valido para essa peca" << std::endl;
					else{
						std::cout << std::endl << "Peca cor " << piece->color << " | Tipo " << piece->type << 
									" Movida de " << colActualPos << rowActualPos << " para: " << colTargetPos << rowTargetPos << std::endl << std::endl;

						done = true; //Sai do player jogada

					}

				}

			}

		}

	}

	turno = BLACK_TURNO;
}

void enemyJogada() {

	std::string coordsSelect;
	std::string coordsTarget;

	bool done = false;
	char col;
	int row;

	while (!done) {

		std::cout << std::endl << std::endl << "Selecione a coordenada da peca a ser movida: ";
		std::getline(std::cin, coordsSelect);

		col = coordsSelect[0];
		row = (int)coordsSelect[1] - 48;

		//Verifica se a peca é valida
		if (!enemy.selecPieceVerif(board, col, row))
			std::cout << std::endl << "ERROR::enemyJogada::enemy.selecPieceVerif:: a peca selecionada nao e valida" << std::endl;
		//Se for válida prossiga...
		else {

			std::cout << "Selecione a coordenada de destino da peca: ";
			std::getline(std::cin, coordsTarget);

			col = coordsTarget[0];
			row = (int)coordsTarget[1] - 48;

			//Verifica se o destino é valido
			if (!enemy.selecDestiVerif(board, col, row))
				std::cout << std::endl << "ERROR::enemyJogada::enemy.selecDestiVerif:: o destino selecionado nao e valida" << std::endl;
			//Se for válido prossiga...
			else {
				//Obtem as posicoes de selecao e de destino
				char colActualPos = tolower(coordsSelect[0]);
				int rowActualPos = (int)coordsSelect[1] - 48;
				char colTargetPos = tolower(coordsTarget[0]);
				int rowTargetPos = (int)coordsTarget[1] - 48;

				const Piece* piece = board.getPiece(colActualPos, rowActualPos);

				//So para ter certeza se o piece foi retornado corretamente
				if (piece == nullptr)
					std::cout << "O ou... ERROR::Main::enemyJogada:: linha aprox 155 piece == nullptr" << std::endl;
				else {
					if (!enemy.makeMovement(board, *piece, colActualPos, rowActualPos, colTargetPos, rowTargetPos))
						std::cout << "ERROR::Main::enemyJogada::makeMovement:: movimento nao e valido para essa peca" << std::endl;
					else {
						std::cout << std::endl << "Peca cor " << piece->color << " | Tipo " << piece->type <<
							" Movida de " << colActualPos << rowActualPos << " para: " << colTargetPos << rowTargetPos << std::endl << std::endl;

						done = true; //Sai do player jogada

					}

				}

			}

		}

	}

	turno = WHITE_TURNO;

}
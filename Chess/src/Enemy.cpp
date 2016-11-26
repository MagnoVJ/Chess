#include "Enemy.h"

//Verifica se colTargetPos e rowTargetPos são validos se não retorna uma mensagem e não atualiza o board
//Verifica se o movimento é permitido
bool Enemy::makeMovement(Board& board, Piece piece, char colActualPos, int rowActualPos, char colTargetPos, int rowTargetPos) {

	if (rowTargetPos < 1 || rowTargetPos > 8) {
		std::cout << "ERRO::Enemy::makeMovement:: row not valid" << std::endl;
		return false;
	}

	if (!(colTargetPos == 'A' || colTargetPos == 'B' || colTargetPos == 'C' || colTargetPos == 'D' || colTargetPos == 'E' || colTargetPos == 'F' || colTargetPos == 'G' || colTargetPos == 'H' || colTargetPos == 'a' || colTargetPos == 'b' || colTargetPos == 'c' || colTargetPos == 'd' || colTargetPos == 'e' || colTargetPos == 'f' || colTargetPos == 'g' || colTargetPos == 'h')) {
		std::cout << "ERRO::Enemy::makeMovement:: col not valid" << std::endl;
		return false;
	}

	if (piece.canMakeaMovementEnemy(colActualPos, rowActualPos, colTargetPos, rowTargetPos, piece.type)) {

		bool castlingLeft = false, castlingRight = false;

		bool movimentoEnPassant = false;

		//Se a peça for diferente de cavalo é necessário verificar se não se está tentando pular peças...
		if (!(piece.type == KNIGHT || piece.type == KING))
			if (!verifPieceOntheWay(board, piece, colActualPos, rowActualPos, colTargetPos, rowTargetPos)) {
				std::cout << std::endl << "ERROR::Enemy::verifPieceIntheWay:: ha peca no caminho, movimento pribido" << std::endl;
				return false;
			}

		if (piece.type == PAWN) {

			if (rowActualPos - 1 == rowTargetPos && colActualPos - 1 == colTargetPos || //Diagonal direita
			   (rowActualPos - 1 == rowTargetPos && colActualPos + 1 == colTargetPos))  //Diagonal esquerda
				if (board.getPiece(colTargetPos, rowTargetPos) == nullptr) {

					//Verifica en passant e altera o movimentoEnPassant
					verifEnpassant(colActualPos, rowActualPos, colTargetPos, rowTargetPos, movimentoEnPassant);

					if (!movimentoEnPassant) {
						std::cout << std::endl << "ERROR::Movimento na diagonal com o peao so é permitido caso for capturar uma peca adversaria" << std::endl;
						return false;
					}

				}

			if (rowActualPos - 1 == rowTargetPos && colActualPos == colTargetPos)
				if (board.getPiece(colTargetPos, rowTargetPos) != nullptr) {
					std::cout << std::endl << "ERROR::Nao e possivel mover com o peao adiante pois tem peca na frente" << std::endl;
					return false;
				}


		}

		if (piece.type == KING) { //Verifica castling

			if (!verifCastling(board, colActualPos, rowActualPos, colTargetPos, rowTargetPos, castlingLeft, castlingRight)) {
				std::cout << std::endl << "ERROR::Erro ao executar Roque" << std::endl;
				return false;

			}
		}

		if (castlingLeft || castlingRight) {

			if (castlingRight) {
				board.setPiece(nullptr, colActualPos, rowActualPos); //Seta a posicao do king como null
				board.setPiece(nullptr, colActualPos - 4, rowActualPos); //Seta a posicao do rock como null
				board.setPiece(new Piece(piece.color, piece.type, false), colTargetPos, rowTargetPos); //Posiciona o rei no target
				board.setPiece(new Piece(piece.color, ROOK, false), colTargetPos + 1, rowTargetPos); //Posiciona o rook no lado esquerdo do rei
			}
			else if (castlingLeft) {
				board.setPiece(nullptr, colActualPos, rowActualPos); //Seta a posicao do king como null
				board.setPiece(nullptr, colActualPos + 3, rowActualPos); //Seta a posicao do rock como null
				board.setPiece(new Piece(piece.color, piece.type, false), colTargetPos, rowTargetPos); //Posiciona o rei no target
				board.setPiece(new Piece(piece.color, ROOK, false), colTargetPos - 1, rowTargetPos); //Posiciona o rook no lado direito do rei
			}

		}
		else {

			if (movimentoEnPassant) {

				board.setPiece(new Piece(piece.color, piece.type, false), colTargetPos, rowTargetPos);
				board.setPiece(nullptr, colActualPos, rowActualPos);

				board.setPiece(nullptr, GameController().enPassant->colPos, GameController().enPassant->rowPos);

			}
			else {

				//Move a peça para a posição target
				//Remove a pessa da posição anterior
				board.setPiece(new Piece(piece.color, piece.type, false), colTargetPos, rowTargetPos);
				board.setPiece(nullptr, colActualPos, rowActualPos);

			}

		}

		//Define o EnPassant se ouver algum
		if (piece.type == PAWN) {

			if (colActualPos == colTargetPos && rowActualPos - 2 == rowTargetPos)
				GameController().enPassant = new EnPassantStruct(colTargetPos, rowTargetPos);
			else
				GameController().enPassant = nullptr;

		}

		return true;

	}

	std::cout << "ERRO::Enemy::makeMovement:: nao foi possivel faser o movimento" << std::endl;
	return false;

}

bool Enemy::verifPieceOntheWay(const Board& board, Piece piece, char colActualPos, int rowActualPos, char colTargetPos, int rowTargetPos) {

	switch (piece.type) {

	case BISHOP: {
		//1º Movement: diagonal direita + cima
		for (int cont = 1; cont <= 7; cont++)
			if ((colActualPos + cont == colTargetPos) && (rowActualPos + cont == rowTargetPos)) {//Achado o destino
																								 //Verifica se tem peca no caminho
				for (int cont2 = 1; !((colActualPos + cont2 == colTargetPos) && (rowActualPos + cont2 == rowTargetPos)); cont2++) {
					if (board.getPiece(colActualPos + cont2, rowActualPos + cont2) != nullptr)
						return false;
				}

				return true;

			}

		//2º Movement: diagonal esquerda + cima
		for (int cont = 1; cont <= 7; cont++)
			if ((colActualPos - cont == colTargetPos) && (rowActualPos + cont == rowTargetPos)) {
				//Verifica se tem peca no caminho
				for (int cont2 = 1; !((colActualPos - cont2 == colTargetPos) && (rowActualPos + cont2 == rowTargetPos)); cont2++)
					if (board.getPiece(colActualPos - cont2, rowActualPos + cont2) != nullptr)
						return false;

				return true;

			}

		//3º Movement: diagonal direita + baixo
		for (int cont = 1; cont <= 7; cont++)
			if ((colActualPos + cont == colTargetPos) && (rowActualPos - cont == rowTargetPos)) {
				//Verifica se tem peca no caminho
				for (int cont2 = 1; !((colActualPos + cont2 == colTargetPos) && (rowActualPos - cont2 == rowTargetPos)); cont2++)
					if (board.getPiece(colActualPos + cont2, rowActualPos - cont2) != nullptr)
						return false;

				return true;

			}

		//4º Movement: diagonal esquerda + baixo
		for (int cont = 1; cont <= 7; cont++)
			if ((colActualPos - cont == colTargetPos) && (rowActualPos - cont == rowTargetPos)) {
				//Verifica se tem peca no caminho
				for (int cont2 = 1; !((colActualPos - cont2 == colTargetPos) && (rowActualPos - cont2 == rowTargetPos)); cont2++)
					if (board.getPiece(colActualPos - cont2, rowActualPos - cont2) != nullptr)
						return false;

				return true;

			}

		std::cout << "NAO PODE CAIR AQUI" << std::endl;

	}
	case ROOK: {

		int xActual, yActual;
		int xTarget, yTarget;

		yActual = rowActualPos - 1;

		if (colActualPos == 'A' || colActualPos == 'B' || colActualPos == 'C' ||
			colActualPos == 'D' || colActualPos == 'E' || colActualPos == 'F' ||
			colActualPos == 'G' || colActualPos == 'H')
			xActual = colActualPos - 65;
		else if (colActualPos == 'a' || colActualPos == 'b' || colActualPos == 'c' ||
			colActualPos == 'd' || colActualPos == 'e' || colActualPos == 'f' ||
			colActualPos == 'g' || colActualPos == 'h')
			xActual = colActualPos - 97;

		yTarget = rowTargetPos - 1;

		if (colTargetPos == 'A' || colTargetPos == 'B' || colTargetPos == 'C' ||
			colTargetPos == 'D' || colTargetPos == 'E' || colTargetPos == 'F' ||
			colTargetPos == 'G' || colTargetPos == 'H')
			xTarget = colTargetPos - 65;
		else if (colTargetPos == 'a' || colTargetPos == 'b' || colTargetPos == 'c' ||
			colTargetPos == 'd' || colTargetPos == 'e' || colTargetPos == 'f' ||
			colTargetPos == 'g' || colTargetPos == 'h')
			xTarget = colTargetPos - 97;

		//Verifica a direita
		for (int cont = 1; xActual + cont <= 7; cont++) {

			Piece* piece = board.getPiece(colActualPos + cont, rowActualPos);

			if (piece != nullptr) {
				//se destino retorna true (encontrou pessa no caminho e é o destino )
				if ((colActualPos + cont == colTargetPos) && (rowActualPos == rowTargetPos))
					return true;
				else
					break;
			}
			else if (piece == nullptr) {
				//se destino retorna true (movendo para uma casa vasia)
				if ((colActualPos + cont == colTargetPos) && (rowActualPos == rowTargetPos))
					return true;
			}
		}

		//Verificar para cima
		for (int cont = 1; yActual + cont <= 7; cont++) {

			Piece* piece = board.getPiece(colActualPos, rowActualPos + cont);

			if (piece != nullptr) {

				if ((colActualPos == colTargetPos) && (rowActualPos + cont == rowTargetPos))
					return true;
				else
					break;
			}
			else if (piece == nullptr) {

				if ((colActualPos == colTargetPos) && (rowActualPos + cont == rowTargetPos))
					return true;

			}
		}

		//Verifica para esquerda
		for (int cont = 1; xActual - cont >= 0; cont++) {

			Piece* piece = board.getPiece(colActualPos - cont, rowActualPos);

			if (piece != nullptr) {

				if ((colActualPos - cont == colTargetPos) && (rowActualPos == rowTargetPos))
					return true;
				else
					break;
			}
			else if (piece == nullptr) {

				if ((colActualPos - cont == colTargetPos) && (rowActualPos == rowTargetPos))
					return true;

			}
		}

		//Verifica para baixo
		for (int cont = 1; yActual - cont >= 0; cont++) {

			Piece* piece = board.getPiece(colActualPos, rowActualPos - cont);

			if (piece != nullptr) {

				if ((colActualPos == colTargetPos) && (rowActualPos - cont == rowTargetPos))
					return true;
				else
					break;

			}
			else if (piece == nullptr) {

				if ((colActualPos == colTargetPos) && (rowActualPos - cont == rowTargetPos))
					return true;

			}
		}

		return false;
	}
	case QUEEN: {
		//Verifica o movimento do bisbo
		//1º Movement: diagonal direita + cima
		for (int cont = 1; cont <= 7; cont++)
			if ((colActualPos + cont == colTargetPos) && (rowActualPos + cont == rowTargetPos)) {//Achado o destino
																								 //Verifica se tem peca no caminho
				for (int cont2 = 1; !((colActualPos + cont2 == colTargetPos) && (rowActualPos + cont2 == rowTargetPos)); cont2++) {
					if (board.getPiece(colActualPos + cont2, rowActualPos + cont2) != nullptr)
						return false;
				}

				return true;

			}

		//2º Movement: diagonal esquerda + cima
		for (int cont = 1; cont <= 7; cont++)
			if ((colActualPos - cont == colTargetPos) && (rowActualPos + cont == rowTargetPos)) {
				//Verifica se tem peca no caminho
				for (int cont2 = 1; !((colActualPos - cont2 == colTargetPos) && (rowActualPos + cont2 == rowTargetPos)); cont2++)
					if (board.getPiece(colActualPos - cont2, rowActualPos + cont2) != nullptr)
						return false;

				return true;

			}

		//3º Movement: diagonal direita + baixo
		for (int cont = 1; cont <= 7; cont++)
			if ((colActualPos + cont == colTargetPos) && (rowActualPos - cont == rowTargetPos)) {
				//Verifica se tem peca no caminho
				for (int cont2 = 1; !((colActualPos + cont2 == colTargetPos) && (rowActualPos - cont2 == rowTargetPos)); cont2++)
					if (board.getPiece(colActualPos + cont2, rowActualPos - cont2) != nullptr)
						return false;

				return true;

			}

		//4º Movement: diagonal esquerda + baixo
		for (int cont = 1; cont <= 7; cont++)
			if ((colActualPos - cont == colTargetPos) && (rowActualPos - cont == rowTargetPos)) {
				//Verifica se tem peca no caminho
				for (int cont2 = 1; !((colActualPos - cont2 == colTargetPos) && (rowActualPos - cont2 == rowTargetPos)); cont2++)
					if (board.getPiece(colActualPos - cont2, rowActualPos - cont2) != nullptr)
						return false;

				return true;

			}

		//Verifica o movimento da torre
		int xActual, yActual;
		int xTarget, yTarget;

		yActual = rowActualPos - 1;

		if (colActualPos == 'A' || colActualPos == 'B' || colActualPos == 'C' ||
			colActualPos == 'D' || colActualPos == 'E' || colActualPos == 'F' ||
			colActualPos == 'G' || colActualPos == 'H')
			xActual = colActualPos - 65;
		else if (colActualPos == 'a' || colActualPos == 'b' || colActualPos == 'c' ||
			colActualPos == 'd' || colActualPos == 'e' || colActualPos == 'f' ||
			colActualPos == 'g' || colActualPos == 'h')
			xActual = colActualPos - 97;

		yTarget = rowTargetPos - 1;

		if (colTargetPos == 'A' || colTargetPos == 'B' || colTargetPos == 'C' ||
			colTargetPos == 'D' || colTargetPos == 'E' || colTargetPos == 'F' ||
			colTargetPos == 'G' || colTargetPos == 'H')
			xTarget = colTargetPos - 65;
		else if (colTargetPos == 'a' || colTargetPos == 'b' || colTargetPos == 'c' ||
			colTargetPos == 'd' || colTargetPos == 'e' || colTargetPos == 'f' ||
			colTargetPos == 'g' || colTargetPos == 'h')
			xTarget = colTargetPos - 97;

		//Verifica a direita
		for (int cont = 1; xActual + cont <= 7; cont++) {

			Piece* piece = board.getPiece(colActualPos + cont, rowActualPos);

			if (piece != nullptr) {
				//se destino retorna true (encontrou pessa no caminho e é o destino )
				if ((colActualPos + cont == colTargetPos) && (rowActualPos == rowTargetPos))
					return true;
				else
					break;
			}
			else if (piece == nullptr) {
				//se destino retorna true (movendo para uma casa vasia)
				if ((colActualPos + cont == colTargetPos) && (rowActualPos == rowTargetPos))
					return true;
			}
		}

		//Verificar para cima
		for (int cont = 1; yActual + cont <= 7; cont++) {

			Piece* piece = board.getPiece(colActualPos, rowActualPos + cont);

			if (piece != nullptr) {

				if ((colActualPos == colTargetPos) && (rowActualPos + cont == rowTargetPos))
					return true;
				else
					break;
			}
			else if (piece == nullptr) {

				if ((colActualPos == colTargetPos) && (rowActualPos + cont == rowTargetPos))
					return true;

			}
		}

		//Verifica para esquerda
		for (int cont = 1; xActual - cont >= 0; cont++) {

			Piece* piece = board.getPiece(colActualPos - cont, rowActualPos);

			if (piece != nullptr) {

				if ((colActualPos - cont == colTargetPos) && (rowActualPos == rowTargetPos))
					return true;
				else
					break;
			}
			else if (piece == nullptr) {

				if ((colActualPos - cont == colTargetPos) && (rowActualPos == rowTargetPos))
					return true;

			}
		}

		//Verifica para baixo
		for (int cont = 1; yActual - cont >= 0; cont++) {

			Piece* piece = board.getPiece(colActualPos, rowActualPos - cont);

			if (piece != nullptr) {

				if ((colActualPos == colTargetPos) && (rowActualPos - cont == rowTargetPos))
					return true;
				else
					break;

			}
			else if (piece == nullptr) {

				if ((colActualPos == colTargetPos) && (rowActualPos - cont == rowTargetPos))
					return true;

			}
		}

		return false;

	}

	case PAWN: {

		if (rowActualPos - 2 == rowTargetPos && colActualPos == colTargetPos) {

			Piece* piece = board.getPiece(colActualPos, rowActualPos - 1);

			if (piece) //Caso piece seja diferente de nullptr == 0 == false tem peca no caminho
				return false;

		}

		return true;

	}


	}

}

bool Enemy::verifCastling(const Board& board, char colActualPos, int rowActualPos, char colTargetPos, int rowTargetPos, bool& castlingLeft, bool& castlingRight) {

	//Tentando fazer o castling pela direita
	if (colActualPos - 2 == colTargetPos && rowActualPos == rowTargetPos) {

		const Piece* king = board.getPiece(colActualPos, rowActualPos);
		const Piece* rock = board.getPiece(colActualPos - 4, rowActualPos);

		if (king != nullptr && rock != nullptr) {

			if (king->neverMoved == true && rock->neverMoved == true) {

				if (board.getPiece(colActualPos - 1, rowActualPos) == nullptr &&
					board.getPiece(colActualPos - 2, rowActualPos) == nullptr &&
					board.getPiece(colActualPos - 3, rowActualPos) == nullptr)
					castlingRight = true;
				else {
					std::cout << std::endl << "ERROR::Roque nao e permitido pois existe peca entre o rei e a torre" << std::endl;
					return false;
				}

			}
			else {
				std::cout << std::endl << "ERROR::Roque nao e permitido pois o rei ou a torre ja foram movidos anteriormente" << std::endl;
				return false;
			}

		}
		else {
			std::cout << std::endl << "ERROR::Roque nao e permitido pois o rei ou a torre nao se encontram na posicao correta" << std::endl;
			return false;
		}

	}

	//Tentando fazer o castling pela esquerda
	if (colActualPos + 2 == colTargetPos && rowActualPos == rowTargetPos) {

		const Piece* king = board.getPiece(colActualPos, rowActualPos);
		const Piece* rock = board.getPiece(colActualPos + 3, rowActualPos);

		if (king != nullptr && rock != nullptr) {

			if (king->neverMoved == true && rock->neverMoved == true) {

				if (board.getPiece(colActualPos + 1, rowActualPos) == nullptr && board.getPiece(colActualPos + 2, rowActualPos) == nullptr)
					castlingRight = true;
				else {
					std::cout << std::endl << "ERROR::Roque nao e permitido pois existe peca entre o rei e a torre" << std::endl;
					return false;
				}

			}
			else {
				std::cout << std::endl << "ERROR::Roque nao e permitido pois o rei ou a torre ja foram movidos anteriormente" << std::endl;
				return false;
			}

		}
		else {
			std::cout << std::endl << "ERROR::Roque nao e permitido pois o rei ou a torre nao se encontram na posicao correta" << std::endl;
			return false;
		}

	}

	return true;

}

bool Enemy::selecPieceVerif(Board board, char col, int row) {

	int x, y;

	if (row < 1 || row > 8) {
		std::cout << "ERRO::Enemy::selecPieceVerif:: row not valid" << std::endl;
		return false;
	}

	y = row - 1;

	if (col == 'A' || col == 'B' || col == 'C' ||
		col == 'D' || col == 'E' || col == 'F' ||
		col == 'G' || col == 'H')
		x = col - 65;
	else if (col == 'a' || col == 'b' || col == 'c' ||
		col == 'd' || col == 'e' || col == 'f' ||
		col == 'g' || col == 'h')
		x = col - 97;
	else {
		std::cout << "ERRO::Enemy::selecPieceVerif:: col not valid" << std::endl;
		return false;
	}

	if (board.pieces[x + y * 8] != nullptr)
		if (board.pieces[x + y * 8]->color == BLACK)
			return true;

	return false;

}

bool Enemy::selecDestiVerif(Board board, char col, int row) {

	int x, y;

	if (row < 1 || row > 8) {
		std::cout << "ERRO::Player::selecDestiVerif:: row not valid" << std::endl;
		return false;
	}

	y = row - 1;

	if (col == 'A' || col == 'B' || col == 'C' ||
		col == 'D' || col == 'E' || col == 'F' ||
		col == 'G' || col == 'H')
		x = col - 65;
	else if (col == 'a' || col == 'b' || col == 'c' ||
		col == 'd' || col == 'e' || col == 'f' ||
		col == 'g' || col == 'h')
		x = col - 97;
	else {
		std::cout << "ERRO::Player::selecDestiVerif:: col not valid" << std::endl;
		return false;
	}

	if (board.pieces[x + y * 8] == nullptr)
		return true;

	if (board.pieces[x + y * 8]->color == BLACK)
		return false;

	return true;

}

void Enemy::verifEnpassant(char colActualPos, int rowActualPos, char colTargetPos, int rowTargetPos, bool& movimentoEnPassant) {

	std::cout << std::endl << "**Verificacao En passant**" << std::endl;

	//Verifica En passant
	if (rowActualPos == 4) { //Verifica se o peao está na 5 casa do tabuleiro

		if (GameController().enPassant) {

			EnPassantStruct posPecEnpassant = *GameController().enPassant;

			if (colTargetPos == posPecEnpassant.colPos && rowTargetPos + 1 == posPecEnpassant.rowPos) {
				std::cout << std::endl << "->Movimento En passant executado" << std::endl;
				movimentoEnPassant = true;
			}

		}
		else
			std::cout << std::endl << "-> Nenhuma pessa se encontra em estado En passant" << std::endl;

	}
	else
		std::cout << std::endl << "->Não e um movimento En passant pois o peao nao se encontra na casa 4" << std::endl;

}
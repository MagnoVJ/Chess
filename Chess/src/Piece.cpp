#include "Piece.h"

bool Piece::canMakeaMovementPlayer(const char colActualPos, const int rowActualPos, const char colTargetPos, const int rowTargetPos, Type type){

	switch(type){

	case KNIGHT:{ 
		//1� movement: duas vezes pra frente uma pra esquerda
		int simMovRow = rowActualPos + 2;
		char simMovCol = colActualPos - 1;
		if((simMovRow == rowTargetPos) && (simMovCol == colTargetPos))
			return true;

		//2� movement: duas vezes pra frente uma pra direita
		simMovRow = rowActualPos + 2;
		simMovCol = colActualPos + 1;
		if((simMovRow == rowTargetPos) && (simMovCol == colTargetPos))
			return true;

		//3� movement: duas vezes pra esquerda uma pra frente
		simMovCol = colActualPos - 2;
		simMovRow = rowActualPos + 1;
		if((simMovRow == rowTargetPos) && (simMovCol == colTargetPos))
			return true;

		//4� movement: duas vezes pra esquerda uma pra tras
		simMovCol = colActualPos - 2;
		simMovRow = rowActualPos - 1;
		if((simMovRow == rowTargetPos) && (simMovCol == colTargetPos))
			return true;

		//5� movement: duas vezes para tras um para esquerda
		simMovRow = rowActualPos - 2;
		simMovCol = colActualPos - 1;
		if((simMovRow == rowTargetPos) && (simMovCol == colTargetPos))
			return true;

		//6� movement: duas vezes para tras um para direita
		simMovRow = rowActualPos - 2;
		simMovCol = colActualPos + 1;
		if((simMovRow == rowTargetPos) && (simMovCol == colTargetPos))
			return true;

		//7� movement: duas vezes para direita um para frente
		simMovCol = colActualPos + 2;
		simMovRow = rowActualPos + 1;
		if((simMovRow == rowTargetPos) && (simMovCol == colTargetPos))
			return true;

		//8� movement: duas vezes para direita um para tras
		simMovCol = colActualPos + 2;
		simMovRow = rowActualPos - 1;
		if((simMovRow == rowTargetPos) && (simMovCol == colTargetPos))
			return true;

		return false;
	}

	case BISHOP:{
		//1� Movement: diagonal direita + cima
		for(int cont = 1; cont <= 7; cont++)
			if((colActualPos + cont == colTargetPos) && (rowActualPos + cont == rowTargetPos))
				return true;

		//2� Movement: diagonal esquerda + cima
		for(int cont = 1; cont <= 7; cont++)
			if((colActualPos - cont == colTargetPos) && (rowActualPos + cont == rowTargetPos))
				return true;
			
		//3� Movement: diagonal direita + baixo
		for(int cont = 1; cont <= 7; cont++)
			if((colActualPos + cont == colTargetPos) && (rowActualPos - cont == rowTargetPos))
				return true;

		//4� Movement: diagonal esquerda + baixo
		for(int cont = 1; cont <= 7; cont++)
			if((colActualPos - cont == colTargetPos) && (rowActualPos - cont == rowTargetPos))
				return true;

		return false;

	}

	case ROOK:{

		if((colActualPos == colTargetPos) || (rowActualPos == rowTargetPos))
			return true;

		return false;


	}

	case QUEEN:{
		//Movimento da torre
		if((colActualPos == colTargetPos) || (rowActualPos == rowTargetPos))
			return true;

		//Movimento do bisbo
		//1� Movement: diagonal direita + cima
		for(int cont = 1; cont <= 7; cont++)
			if((colActualPos + cont == colTargetPos) && (rowActualPos + cont == rowTargetPos))
				return true;

		//2� Movement: diagonal esquerda + cima
		for(int cont = 1; cont <= 7; cont++)
			if((colActualPos - cont == colTargetPos) && (rowActualPos + cont == rowTargetPos))
				return true;
			
		//3� Movement: diagonal direita + baixo
		for(int cont = 1; cont <= 7; cont++)
			if((colActualPos + cont == colTargetPos) && (rowActualPos - cont == rowTargetPos))
				return true;

		//4� Movement: diagonal esquerda + baixo
		for(int cont = 1; cont <= 7; cont++)
			if((colActualPos - cont == colTargetPos) && (rowActualPos - cont == rowTargetPos))
				return true;

		return false;

	}

	case KING: {

		if((colActualPos + 1 == colTargetPos && rowActualPos     == rowTargetPos) || //Mover para direita
		   (colActualPos + 1 == colTargetPos && rowActualPos + 1 == rowTargetPos) || //Mover para diagonal direita frente
		   (colActualPos     == colTargetPos && rowActualPos + 1 == rowTargetPos) || //Mover para frente
		   (colActualPos - 1 == colTargetPos && rowActualPos + 1 == rowTargetPos) || //Mover para diagonal esquerda frente
		   (colActualPos - 1 == colTargetPos && rowActualPos     == rowTargetPos) || //Mover para esquerda
		   (colActualPos - 1 == colTargetPos && rowActualPos - 1 == rowTargetPos) || //Mover para diagonal esquerda tr�s
		   (colActualPos     == colTargetPos && rowActualPos - 1 == rowTargetPos) || //Mover para tr�s
		   (colActualPos + 1 == colTargetPos && rowActualPos - 1 == rowTargetPos))  //Mover para diagonal direita tr�s
			return true;

		//Verifica Castling
		if (colActualPos + 2 == colTargetPos && rowActualPos == rowTargetPos) //Castling pela direita
			return true;
		else if (colActualPos - 2 == colTargetPos && rowActualPos == rowTargetPos) //Castling pela esquerda
			return true;

		return false;

	}

	case PAWN: {

		if (rowActualPos + 1 == rowTargetPos && colActualPos == colTargetPos) //Simples movimento de andar para frente
			return true;
		else if (rowActualPos + 2 == rowTargetPos && colActualPos == colTargetPos) { //Movimento duas casas para frente (so permitido se for a primeira jogada do peao)

			if (this->neverMoved)
				return true;
			else {
				std::cout << std::endl << "ERROR::Mover duas casas a diante com o peao so e permitido caso seja o primeiro movimento do mesmo" << std::endl;
				return false;
			}

		}
		else if(rowActualPos + 1 == rowTargetPos && colActualPos + 1 == colTargetPos || //Diagonal direita
			   (rowActualPos + 1 == rowTargetPos && colActualPos - 1 == colTargetPos))  //Diagonal esquerda
			return true;

		return false;

	}
     

	}

	std::cout << "ERROR::Piece::canMakeaMovement::switch:: nao foi encontrado um tipo para pe�a" << std::endl;

}

bool Piece::canMakeaMovementEnemy(const char colActualPos, const int rowActualPos, const char colTargetPos, const int rowTargetPos, Type type){

	switch (type) {

	case KNIGHT: {
		//1� movement: duas vezes pra frente uma pra esquerda
		int simMovRow = rowActualPos - 2;
		char simMovCol = colActualPos + 1;
		if ((simMovRow == rowTargetPos) && (simMovCol == colTargetPos))
			return true;

		//2� movement: duas vezes pra frente uma pra direita
		simMovRow = rowActualPos - 2;
		simMovCol = colActualPos - 1;
		if ((simMovRow == rowTargetPos) && (simMovCol == colTargetPos))
			return true;

		//3� movement: duas vezes pra esquerda uma pra frente
		simMovCol = colActualPos + 2;
		simMovRow = rowActualPos - 1;
		if ((simMovRow == rowTargetPos) && (simMovCol == colTargetPos))
			return true;

		//4� movement: duas vezes pra esquerda uma pra tras
		simMovCol = colActualPos + 2;
		simMovRow = rowActualPos + 1;
		if ((simMovRow == rowTargetPos) && (simMovCol == colTargetPos))
			return true;

		//5� movement: duas vezes para tras um para esquerda
		simMovRow = rowActualPos + 2;
		simMovCol = colActualPos + 1;
		if ((simMovRow == rowTargetPos) && (simMovCol == colTargetPos))
			return true;

		//6� movement: duas vezes para tras um para direita
		simMovRow = rowActualPos + 2;
		simMovCol = colActualPos - 1;
		if ((simMovRow == rowTargetPos) && (simMovCol == colTargetPos))
			return true;

		//7� movement: duas vezes para direita um para frente
		simMovCol = colActualPos - 2;
		simMovRow = rowActualPos - 1;
		if ((simMovRow == rowTargetPos) && (simMovCol == colTargetPos))
			return true;

		//8� movement: duas vezes para direita um para tras
		simMovCol = colActualPos - 2;
		simMovRow = rowActualPos + 1;
		if ((simMovRow == rowTargetPos) && (simMovCol == colTargetPos))
			return true;

		return false;

	}

	case BISHOP: {
		//1� Movement: diagonal direita + cima
		for (int cont = 1; cont <= 7; cont++)
			if ((colActualPos + cont == colTargetPos) && (rowActualPos + cont == rowTargetPos))
				return true;

		//2� Movement: diagonal esquerda + cima
		for (int cont = 1; cont <= 7; cont++)
			if ((colActualPos - cont == colTargetPos) && (rowActualPos + cont == rowTargetPos))
				return true;

		//3� Movement: diagonal direita + baixo
		for (int cont = 1; cont <= 7; cont++)
			if ((colActualPos + cont == colTargetPos) && (rowActualPos - cont == rowTargetPos))
				return true;

		//4� Movement: diagonal esquerda + baixo
		for (int cont = 1; cont <= 7; cont++)
			if ((colActualPos - cont == colTargetPos) && (rowActualPos - cont == rowTargetPos))
				return true;

		return false;

	}

	case ROOK: {

		if ((colActualPos == colTargetPos) || (rowActualPos == rowTargetPos))
			return true;

		return false;

	}

	case QUEEN: {
		//Movimento da torre
		if ((colActualPos == colTargetPos) || (rowActualPos == rowTargetPos))
			return true;

		//Movimento do bisbo
		//1� Movement: diagonal direita + cima
		for (int cont = 1; cont <= 7; cont++)
			if ((colActualPos + cont == colTargetPos) && (rowActualPos + cont == rowTargetPos))
				return true;

		//2� Movement: diagonal esquerda + cima
		for (int cont = 1; cont <= 7; cont++)
			if ((colActualPos - cont == colTargetPos) && (rowActualPos + cont == rowTargetPos))
				return true;

		//3� Movement: diagonal direita + baixo
		for (int cont = 1; cont <= 7; cont++)
			if ((colActualPos + cont == colTargetPos) && (rowActualPos - cont == rowTargetPos))
				return true;

		//4� Movement: diagonal esquerda + baixo
		for (int cont = 1; cont <= 7; cont++)
			if ((colActualPos - cont == colTargetPos) && (rowActualPos - cont == rowTargetPos))
				return true;

		return false;

	}

	case KING: {

		if ((colActualPos + 1 == colTargetPos && rowActualPos == rowTargetPos) || //Mover para direita
			(colActualPos + 1 == colTargetPos && rowActualPos + 1 == rowTargetPos) || //Mover para diagonal direita frente
			(colActualPos == colTargetPos && rowActualPos + 1 == rowTargetPos) || //Mover para frente
			(colActualPos - 1 == colTargetPos && rowActualPos + 1 == rowTargetPos) || //Mover para diagonal esquerda frente
			(colActualPos - 1 == colTargetPos && rowActualPos == rowTargetPos) || //Mover para esquerda
			(colActualPos - 1 == colTargetPos && rowActualPos - 1 == rowTargetPos) || //Mover para diagonal esquerda tr�s
			(colActualPos == colTargetPos && rowActualPos - 1 == rowTargetPos) || //Mover para tr�s
			(colActualPos + 1 == colTargetPos && rowActualPos - 1 == rowTargetPos))  //Mover para diagonal direita tr�s
			return true;

		//Verifica Castling
		if (colActualPos + 2 == colTargetPos && rowActualPos == rowTargetPos) //Castling pela esquerda
			return true;
		else if (colActualPos - 2 == colTargetPos && rowActualPos == rowTargetPos) //Castling pela direita
			return true;

		return false;

	}

	case PAWN: {

		if (rowActualPos - 1 == rowTargetPos && colActualPos == colTargetPos) //Simples movimento de andar para frente
			return true;
		else if (rowActualPos - 2 == rowTargetPos && colActualPos == colTargetPos) { //Movimento duas casas para frente (so permitido se for a primeira jogada do peao)
			
			if (this->neverMoved)
				return true;
			else {
				std::cout << std::endl << "ERROR::Mover duas casas a diante com o peao so e permitido caso seja o primeiro movimento do mesmo" << std::endl;
				return false;
			}


		}
		else if (rowActualPos - 1 == rowTargetPos && colActualPos - 1 == colTargetPos || //Diagonal direita
			    (rowActualPos - 1 == rowTargetPos && colActualPos + 1 == colTargetPos))  //Diagonal esquerda
			return true;

		return false;

	}

	}

	std::cout << "ERROR::Piece::canMakeaMovement::switch:: nao foi encontrado um tipo para pe�a" << std::endl;

}
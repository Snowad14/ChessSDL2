#include "Piece.hpp"

std::vector<Piece*> Piece::boards_pieces;

Piece::Piece(int x, int y, Color color, SDL_Texture* texture) {
	this->x = x;
	this->y = y;
	this->color = color;
	this->texture = texture;
}

int Piece::getX() {
	return x;
}

int Piece::getY() {
	return y;
}

Color Piece::getColor() {
	return color;
}

SDL_Texture* Piece::getTexture() {
	return texture;
}

std::vector<std::pair<int, int>> Piece::filterMoves(std::vector<std::pair<int, int>> moves) {

	for (int i = 0; i < moves.size(); i++) {
		// Enlevez les coups qui sont hors du plateau ou qui sont la position actuelle
		if (moves[i].first < 0 || moves[i].first > 7 || moves[i].second < 0 || moves[i].second > 7 || moves[i].first == x && moves[i].second == y) {
			moves.erase(moves.begin() + i);
			i--;
			continue;
		}

		for (auto piece : Piece::boards_pieces) {
			// Supprimer les mouvements qui sont sur une pièce de la même couleur
			if (piece->getX() == moves[i].first && piece->getY() == moves[i].second && piece->color == color) {
				moves.erase(moves.begin() + i);
				i--;
				break;
			}

		}
	}


	return moves;
}

void Piece::move(int x, int y) {
	this->x = x;
	this->y = y;
}
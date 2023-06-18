#include "Tour.hpp"

Tour::Tour(int x, int y, Color color, SDL_Texture* texture) : Piece(x, y, color, texture) {}

std::vector<std::pair<int, int>> Tour::getAvailableMoves() {
	std::vector<std::pair<int, int>> moves;

	bool horizontal_droite = true;
	bool horizontal_gauche = true;
	bool vertical_haut = true;
	bool vertical_bas = true;

	for (int i = 1; i < 8; i++) {

		if (horizontal_droite) {
			moves.push_back(std::make_pair(x + i, y));
			for (const auto piece : Piece::boards_pieces) {
				if (piece->getX() == x + i && piece->getY() == y) {
					horizontal_droite = false;
					if (piece->getColor() != this->getColor()) {
						moves.push_back(std::make_pair(x + i, y));
					}
					break;
				}
			}
		}

		if (horizontal_gauche) {
			moves.push_back(std::make_pair(x - i, y));
			for (const auto piece : Piece::boards_pieces) {
				if (piece->getX() == x - i && piece->getY() == y) {
					horizontal_gauche = false;
					if (piece->getColor() != this->getColor()) {
						moves.push_back(std::make_pair(x - i, y));
					}
					break;
				}
			}
		}

		if (vertical_haut) {
			moves.push_back(std::make_pair(x, y - i));
			for (const auto piece : Piece::boards_pieces) {
				if (piece->getX() == x && piece->getY() == y - i) {
					vertical_haut = false;
					if (piece->getColor() != this->getColor()) {
						moves.push_back(std::make_pair(x, y - i));
					}
					break;
				}
			}
		}

		if (vertical_bas) {
			moves.push_back(std::make_pair(x, y + i));
			for (const auto piece : Piece::boards_pieces) {
				if (piece->getX() == x && piece->getY() == y + i) {
					vertical_bas = false;
					if (piece->getColor() != this->getColor()) {
						moves.push_back(std::make_pair(x, y + i));
					}
					break;
				}
			}
		}

	}

	return filterMoves(moves);
}
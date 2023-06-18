#include "Fou.hpp"

Fou::Fou(int x, int y, Color color, SDL_Texture* texture) : Piece(x, y, color, texture) {}

std::vector<std::pair<int, int>> Fou::getAvailableMoves() {
	std::vector<std::pair<int, int>> moves;

	bool diagonale_haut_droit = true;
	bool diagonale_haut_gauche = true;
	bool diagonale_bas_droit = true;
	bool diagonale_bas_gauche = true;

	for (int i = 1; i < 8; i++) {

		if (diagonale_haut_droit) {
			moves.push_back(std::make_pair(x + i, y + i));
			for (const auto piece : Piece::boards_pieces) {
				if (piece->getX() == x + i && piece->getY() == y + i) {
					diagonale_haut_droit = false;
					if (piece->getColor() != this->getColor()) {
						moves.push_back(std::make_pair(x + i, y + i));
					}
					break;
				}
			}
		}

		if (diagonale_haut_gauche) {
			moves.push_back(std::make_pair(x - i, y - i));
			for (const auto piece : Piece::boards_pieces) {
				if (piece->getX() == x - i && piece->getY() == y - i) {
					diagonale_haut_gauche = false;
					if (piece->getColor() != this->getColor()) {
						moves.push_back(std::make_pair(x - i, y - i));
					}
					break;
				}
			}
		}

		if (diagonale_bas_droit) {
			moves.push_back(std::make_pair(x + i, y - i));
			for (const auto piece : Piece::boards_pieces) {
				if (piece->getX() == x + i && piece->getY() == y - i) {
					diagonale_bas_droit = false;
					if (piece->getColor() != this->getColor()) {
						moves.push_back(std::make_pair(x + i, y - i));
					}
					break;
				}
			}
		}

		if (diagonale_bas_gauche) {
			moves.push_back(std::make_pair(x - i, y + i));
			for (const auto piece : Piece::boards_pieces) {
				if (piece->getX() == x - i && piece->getY() == y + i) {
					diagonale_bas_gauche = false;
					if (piece->getColor() != this->getColor()) {
						moves.push_back(std::make_pair(x - i, y + i));
					}
					break;
				}
			}
		}

	}

	return filterMoves(moves);
	
}
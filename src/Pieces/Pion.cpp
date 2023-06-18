#include "Pion.hpp"

Pion::Pion(int x, int y, Color color, SDL_Texture* texture) : Piece(x, y, color, texture) {}

std::vector<std::pair<int, int>> Pion::getAvailableMoves() {
	std::vector<std::pair<int, int>> moves;

	bool canFrontMoove = true;
	bool canFrontMooveBig = true;

	const int posOffset = color == Color::WHITE ? 1 : -1;
	const int startPosY = color == Color::WHITE ? 1 : 6;

	for (auto piece : Piece::boards_pieces) {
		if (piece->getX() == x + 1 && piece->getY() == y + posOffset) {
			moves.push_back(std::make_pair(x + 1, y + posOffset));
		}
		if (piece->getX() == x - 1 && piece->getY() == y + posOffset) {
			moves.push_back(std::make_pair(x - 1, y + posOffset));
		}
		if (piece->getX() == x && piece->getY() == y + posOffset) {
			canFrontMoove = false;
		}
		if (piece->getX() == x && piece->getY() == y + posOffset * 2) {
			canFrontMooveBig = false;
		}
	}
	if (canFrontMoove) {
		if (y == startPosY && canFrontMooveBig) {
			moves.push_back(std::make_pair(x, y + posOffset * 2));
		}
		moves.push_back(std::make_pair(x, y + posOffset));
	}

	/*
	if (color == Color::WHITE) {
		for (auto piece : Piece::boards_pieces) {
			if (piece->getX() == x + 1 && piece->getY() == y + 1) {
				moves.push_back(std::make_pair(x + 1, y + 1));
			}
			if (piece->getX() == x - 1 && piece->getY() == y + 1) {
				moves.push_back(std::make_pair(x - 1, y + 1));
			}
			if (piece->getX() == x && piece->getY() == y + 1) {
				canFrontMoove = false;
			}
			if (piece->getX() == x && piece->getY() == y + 2) {
				canFrontMooveBig = false;
			}
		}
		if (canFrontMoove) {
			if (y == 1 && canFrontMooveBig) {
				moves.push_back(std::make_pair(x, y + 2));	
			}
			moves.push_back(std::make_pair(x, y + 1));
		}
	}

	if (color == Color::BLACK) {
		for (auto piece : Piece::boards_pieces) {
			if (piece->getX() == x + 1 && piece->getY() == y - 1) {
				moves.push_back(std::make_pair(x + 1, y - 1));
			}
			if (piece->getX() == x - 1 && piece->getY() == y - 1) {
				moves.push_back(std::make_pair(x - 1, y - 1));
			}
			if (piece->getX() == x && piece->getY() == y - 1) {
				canFrontMoove = false;
			}
			if (piece->getX() == x && piece->getY() == y - 2) {
				canFrontMooveBig = false;
			}
		}
		if (canFrontMoove) {
			if (y == 6 && canFrontMooveBig) {
				moves.push_back(std::make_pair(x, y - 2));
			}
			moves.push_back(std::make_pair(x, y - 1));

		}
	}
	*/

	return filterMoves(moves);
}
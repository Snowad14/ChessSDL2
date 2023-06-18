#include "Roi.hpp"

Roi::Roi(int x, int y, Color color, SDL_Texture* texture) : Piece(x, y, color, texture) {}

std::vector<std::pair<int, int>> Roi::getAvailableMoves() {
    std::vector<std::pair<int, int>> moves;

    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
			moves.push_back(std::make_pair(i, j));
		}   
    }

    return filterMoves(moves);
}
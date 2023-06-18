#include "Cavalier.hpp"

Cavalier::Cavalier(int x, int y, Color color, SDL_Texture* texture) : Piece(x, y, color, texture) {}

std::vector<std::pair<int, int>> Cavalier::getAvailableMoves() {
    std::vector<std::pair<int, int>> moves;
    moves.push_back(std::make_pair(x + 2, y + 1));
    moves.push_back(std::make_pair(x + 2, y - 1));
    moves.push_back(std::make_pair(x - 2, y + 1));
    moves.push_back(std::make_pair(x - 2, y - 1));
    moves.push_back(std::make_pair(x + 1, y + 2));
    moves.push_back(std::make_pair(x + 1, y - 2));
    moves.push_back(std::make_pair(x - 1, y + 2));
    moves.push_back(std::make_pair(x - 1, y - 2));
    return filterMoves(moves);
}
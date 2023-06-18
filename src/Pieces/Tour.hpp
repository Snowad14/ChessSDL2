#pragma once
#include "Piece.hpp"

class Tour : public Piece {

public:
    Tour(int x, int y, Color color, SDL_Texture* texture);

    std::vector<std::pair<int, int>> getAvailableMoves() override;

};


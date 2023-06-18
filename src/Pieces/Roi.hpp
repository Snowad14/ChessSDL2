#pragma once
#include "Piece.hpp"

class Roi : public Piece {

public:
    Roi(int x, int y, Color color, SDL_Texture* texture);

    std::vector<std::pair<int, int>> getAvailableMoves() override;

};


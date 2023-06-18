#pragma once
#include "Piece.hpp"

class Dame : public Piece {

public:
    Dame(int x, int y, Color color, SDL_Texture* texture);

    std::vector<std::pair<int, int>> getAvailableMoves() override;

};


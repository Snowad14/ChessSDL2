#pragma once
#include "Piece.hpp"

class Cavalier : public Piece {

public:
    Cavalier(int x, int y, Color color, SDL_Texture* texture);

    std::vector<std::pair<int, int>> getAvailableMoves() override;

};


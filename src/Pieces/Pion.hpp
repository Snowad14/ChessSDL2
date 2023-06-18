#pragma once
#include "Piece.hpp"

class Pion : public Piece {

public:
    Pion(int x, int y, Color color, SDL_Texture* texture);


    std::vector<std::pair<int, int>> getAvailableMoves() override;

};


#pragma once
#include "Piece.hpp"

class Fou : public Piece {

public:
    Fou(int x, int y, Color color, SDL_Texture* texture);

    
    std::vector<std::pair<int, int>> getAvailableMoves() override;

};


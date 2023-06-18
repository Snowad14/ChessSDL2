#include "Dame.hpp"

Dame::Dame(int x, int y, Color color, SDL_Texture* texture) : Piece(x, y, color, texture) {}

std::vector<std::pair<int, int>> Dame::getAvailableMoves() {
	std::vector<std::pair<int, int>> moves;

	// Je sais que ce j'ai fait pour le fou & la tour est pas opti, donc j'utilise ce qu'il faudrait vraiment faire ici mais j'ai du regarder sur internet

    const int dx[] = { 1, -1, -1, 1, 0, 0, 1, -1 };
    const int dy[] = { 1, -1, 1, -1, 1, -1, 0, 0 };

    for (int i = 0; i < 8; i++) {
        for (int j = 1; j < 8; j++) {
            int nx = x + j * dx[i];
            int ny = y + j * dy[i];
            bool blocked = false;
            for (const auto& piece : Piece::boards_pieces) {
                if (piece->getX() == nx && piece->getY() == ny) {
                    if (piece->getColor() != color) {
                        moves.push_back(std::make_pair(nx, ny));
                    }
                    blocked = true;
                    break;
                }
            }
            if (blocked) {
                break;
            }
            moves.push_back(std::make_pair(nx, ny));
        }
    }

    return filterMoves(moves);
}
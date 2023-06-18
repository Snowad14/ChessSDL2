#pragma once
#include <iostream>
#include <vector>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

enum class Color {
	BLACK,
	WHITE
};

class Piece {

protected:
	int x, y;
	Color color;
	SDL_Texture* texture;

	Piece(int x, int y, Color color, SDL_Texture* texture);

public:
	static std::vector<Piece*> boards_pieces;
	virtual std::vector<std::pair<int, int>> getAvailableMoves() = 0;
	std::vector<std::pair<int, int>> filterMoves(std::vector<std::pair<int, int>> moves);
	int getX();
	int getY();
	Color getColor();
	SDL_Texture* getTexture();
	void move(int x, int y);
};

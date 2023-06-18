#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Pieces/Piece.hpp"
#include "Pieces/Cavalier.hpp"
#include "Pieces/Tour.hpp"
#include "Pieces/Fou.hpp"
#include "Pieces/Dame.hpp"
#include "Pieces/Roi.hpp"
#include "Pieces/Pion.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int TILE_SIZE = 100;
auto& boards_pieces = Piece::boards_pieces;

template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface* tour_blanc = IMG_Load("assets/blanc/tour.png");
	SDL_Surface* cavalier_blanc = IMG_Load("assets/blanc/cavalier.png");
	SDL_Surface* fou_blanc = IMG_Load("assets/blanc/fou.png");
	SDL_Surface* dame_blanc = IMG_Load("assets/blanc/dame.png");
	SDL_Surface* roi_blanc = IMG_Load("assets/blanc/roi.png");
	SDL_Surface* pion_blanc = IMG_Load("assets/blanc/pion.png");

	SDL_Surface* tour_noir = IMG_Load("assets/noir/tour.png");
	SDL_Surface* cavalier_noir = IMG_Load("assets/noir/cavalier.png");
	SDL_Surface* fou_noir = IMG_Load("assets/noir/fou.png");
	SDL_Surface* dame_noir = IMG_Load("assets/noir/dame.png");
	SDL_Surface* roi_noir = IMG_Load("assets/noir/roi.png");
	SDL_Surface* pion_noir = IMG_Load("assets/noir/pion.png");

	// Pieces Blanches
	boards_pieces.push_back(new Tour(0, 0, Color::WHITE, SDL_CreateTextureFromSurface(renderer, tour_blanc)));
	boards_pieces.push_back(new Cavalier(1, 0, Color::WHITE, SDL_CreateTextureFromSurface(renderer, cavalier_blanc)));
	boards_pieces.push_back(new Fou(2, 0, Color::WHITE, SDL_CreateTextureFromSurface(renderer, fou_blanc)));
	boards_pieces.push_back(new Dame(3, 0, Color::WHITE, SDL_CreateTextureFromSurface(renderer, dame_blanc)));
	boards_pieces.push_back(new Roi(4, 0, Color::WHITE, SDL_CreateTextureFromSurface(renderer, roi_blanc)));
	boards_pieces.push_back(new Fou(5, 0, Color::WHITE, SDL_CreateTextureFromSurface(renderer, fou_blanc)));
	boards_pieces.push_back(new Cavalier(6, 0, Color::WHITE, SDL_CreateTextureFromSurface(renderer, cavalier_blanc)));
	boards_pieces.push_back(new Tour(7, 0, Color::WHITE, SDL_CreateTextureFromSurface(renderer, tour_blanc)));
	for (int i = 0; i < 8; i++) {
		boards_pieces.push_back(new Pion(i, 1, Color::WHITE, SDL_CreateTextureFromSurface(renderer, pion_blanc)));
	}

	// Pieces Noires
	boards_pieces.push_back(new Tour(0, 7, Color::BLACK, SDL_CreateTextureFromSurface(renderer, tour_noir)));
	boards_pieces.push_back(new Cavalier(1, 7, Color::BLACK, SDL_CreateTextureFromSurface(renderer, cavalier_noir)));
	boards_pieces.push_back(new Fou(2, 7, Color::BLACK, SDL_CreateTextureFromSurface(renderer, fou_noir)));
	boards_pieces.push_back(new Dame(3, 7, Color::BLACK, SDL_CreateTextureFromSurface(renderer, dame_noir)));
	boards_pieces.push_back(new Roi(4, 7, Color::BLACK, SDL_CreateTextureFromSurface(renderer, roi_noir)));
	boards_pieces.push_back(new Fou(5, 7, Color::BLACK, SDL_CreateTextureFromSurface(renderer, fou_noir)));
	boards_pieces.push_back(new Cavalier(6, 7, Color::BLACK, SDL_CreateTextureFromSurface(renderer, cavalier_noir)));
	boards_pieces.push_back(new Tour(7, 7, Color::BLACK, SDL_CreateTextureFromSurface(renderer, tour_noir)));
	for (int i = 0; i < 8; i++) {
		boards_pieces.push_back(new Pion(i, 6, Color::BLACK, SDL_CreateTextureFromSurface(renderer, pion_noir)));
	}

	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Color light_green = { 0, 255, 0, 255 };
	std::vector<std::pair<int, int>> possible_moves;
	Piece* selected_piece = nullptr;
	Color color_turn = Color::WHITE;
	bool quit = false;

	while (!quit) {

		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) quit = true;

			if (event.type == SDL_MOUSEBUTTONDOWN) {

				int x = event.button.x / TILE_SIZE;
				int y = event.button.y / TILE_SIZE;

				if (selected_piece != nullptr) {
					// vérifier si le clic est sur une case valide
					for (auto move : possible_moves) {
						if (move.first == x && move.second == y) {

							for (auto piece : boards_pieces) {
								if (piece->getX() == x && piece->getY() == y) {

									if (instanceof<Roi>(piece)) {
										printf("Victoire des %s\n", color_turn == Color::WHITE ? "blancs" : "noirs");
									}

									boards_pieces.erase(std::remove(boards_pieces.begin(), boards_pieces.end(), piece), boards_pieces.end());
									delete piece;
									break;
								}
							}

							selected_piece->move(x, y);
							selected_piece = nullptr;
							color_turn = color_turn == Color::WHITE ? Color::BLACK : Color::WHITE;
							break;
						}
					}
				}

				// vérifier s'il y a une pièce à la position du clic
				for (auto piece : boards_pieces) {
					if (piece->getX() == x && piece->getY() == y) {
						if (piece->getColor() != color_turn) break;
						selected_piece = piece; // sélectionner la pièce
					}
				}

			}
		}


		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {

				// Détermine la couleur du carré 
				SDL_Color square_color = (i + j) % 2 == 0 ? white : light_green;
				SDL_Rect square_rect = { j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE };

				// Dessine le carré
				SDL_SetRenderDrawColor(renderer, square_color.r, square_color.g, square_color.b, square_color.a);
				SDL_RenderFillRect(renderer, &square_rect);

				//  Vérifie s'il y a une pièce à la position actuelle
				for (auto piece : boards_pieces) {
					if (piece->getX() == j && piece->getY() == i) {
						// Réduire la taille de la pièce pour qu'elle soit plus petite que le carré et donc plus jolie
						SDL_Rect piece_rect = { j * TILE_SIZE + TILE_SIZE * 0.1, i * TILE_SIZE + TILE_SIZE * 0.1, TILE_SIZE * 0.8, TILE_SIZE * 0.8 };
						SDL_RenderCopy(renderer, piece->getTexture(), NULL, &piece_rect);
					}
				}

				// Dessine un cercle rouge au centre du carré si la pièce est sélectionnée et que le mouvement est possible
				if (selected_piece != nullptr) {
					for (auto possible_move : selected_piece->getAvailableMoves()) {
						if (possible_move.first == j && possible_move.second == i) {
							SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
							SDL_Rect circle_rect = { j * TILE_SIZE + TILE_SIZE / 2 - TILE_SIZE / 8, i * TILE_SIZE + TILE_SIZE / 2 - TILE_SIZE / 8, TILE_SIZE / 4, TILE_SIZE / 4 };
							SDL_RenderFillRect(renderer, &circle_rect);
						}
					}
					possible_moves = selected_piece->getAvailableMoves();
				}
			}
		}

		SDL_RenderPresent(renderer);
	}



}

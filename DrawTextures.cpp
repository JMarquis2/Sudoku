/*
#include <SFML/Graphics.hpp>
#include <vector>
void drawBoard(sf::RenderWindow* window, std::vector<sf::Sprite*>* sprites, std::vector<std::vector<int>>* numbers) {
	window->clear(sf::Color::White);
	window->draw(*(*sprites)[0]);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			window->draw(*(*sprites)[(*numbers)[i][j]]);
		}
	}
};
*/
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
int solvePuzzle(std::vector<std::vector<int>>* puzzle);
int improvedSolvePuzzle(std::vector<std::vector<int>>* puzzle);
int improvedSolvePuzzleInSteps(std::vector<std::vector<int>>* puzzle, sf::RenderWindow* window, std::vector<sf::Sprite*>* sprites);
int solvePuzzleInSteps(std::vector<std::vector<int>>* puzzle, sf::RenderWindow* window, std::vector<sf::Sprite*>* sprites);


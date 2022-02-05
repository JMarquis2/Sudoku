#pragma once
#pragma once
#include <SFML/Graphics.hpp>
class Button
{
public:
	bool clicked = false;
	int top;
	int bot;
	int right;
	int left;
	bool Contains(sf::Vector2i pos);
	Button(sf::FloatRect border);
	void Click();
};
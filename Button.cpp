#include "Button.h"
Button::Button(sf::FloatRect border) {
	clicked = false;
	top = border.top;
	bot = border.top + border.height;
	left = border.left;
	right = border.left + border.width;
}
bool Button::Contains(sf::Vector2i pos) {
	int x = pos.x;
	int y = pos.y;
	if (x < right && x > left&& y < bot && y > top)
		return true;
	return false;
}
void Button::Click() {
	if (clicked == true)
		clicked = false;
	else
		clicked = true;
}
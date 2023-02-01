#include "DrawBoard.h"
void drawBoard(sf::RenderWindow* window, std::vector<sf::Sprite*>* sprites, std::vector<std::vector<int>>* numbers) {
    window->clear(sf::Color::White);
    window->draw(*(*sprites)[0]);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            //-1 is the value associated with a blank space.
            if ((*numbers)[i][j] == -1) {}
            /*sets the position of the sprite. Steps:
            (1) Access sprite by using the value of the space as an index.
            (2) Since the sudoku board is made up of spaces of length 60, set borders of length 10, and space boarders of length 5, We begin with first set boarder (10) and add i/3 * 5 to account for extra lengths
            of next 2 set boarders. Then, simply add 5*i to account for space boarders and 60*i to account for space lengths and that gives the value of the top-left pixel of each respective space.
            (3) Then, since the numbers themselves are 50x30, add either 5 or 15 to the calculation (for vertical or horizontal positions)
            (4) Finally, print.
            */
            else {
                (*(*sprites)[(*numbers)[i][j]]).setPosition(sf::Vector2f(25 + 5 * (i / 3) + 65 * i, 15 + 5 * (j / 3) + 65 * j));
                window->draw(*(*sprites)[(*numbers)[i][j]]);
            }
        }
    }
};
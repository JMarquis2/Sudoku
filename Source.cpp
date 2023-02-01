#include <SFML/Graphics.hpp>
#include "Import.h"
#include "Solves.h"
#include "DrawBoard.h"
#include <vector>
#include <cstdlib>
#include <stack>
#include <ctime>
#include <unordered_map>
#include <iostream>
#include "Tried.cpp"
#include <unordered_set>
using std::unordered_map;
using std::vector;
using std::stack;
int main()
{
    //=============Initialization=============//
    sf::RenderWindow window(sf::VideoMode(610, 610), "Sudoku");
    window.setFramerateLimit(30);
    std::vector<sf::Texture> textures(10);
    std::vector<sf::Sprite*> sprites;
    importSpritesFromFiles(&textures, &sprites);

    std::vector<std::vector<int>> numbers;
    std::string example = "030000400000043602050001000060000074070000030509000000007009360100206090000070000";
    std::string example1 = "700009040000000305050001700000000000400008060002010070040020036500030000800060010";

    std::string empty = "000000000000000000000000000000000000000000000000000000000000000000000000000000000";

    for (int i = 0; i < 9; i++){
        std::vector<int> ones(9, i+1);
        numbers.push_back(ones);
    }
    int i = 0;
    for (int j = 0; j < 81; j++) {
        numbers[i][j / 9] = example[j] - 48;
        if (numbers[i][j / 9] == 0)
            numbers[i][j / 9] = -1;
        i = (i + 1) % 9;
    }
    if (solvePuzzle(&numbers) == -1) std::cout << "error in solve puzzle" << std::endl;
    //if (improvedSolvePuzzle(&numbers) == -1) std::cout << "error in solve puzzle" << std::endl;
    //if (solvePuzzleInSteps(&numbers, &window, &sprites) == -1) std::cout << "error in solve puzzle" << std::endl;
    //if (improvedSolvePuzzleInSteps(&numbers, &window, &sprites) == -1) std::cout << "error in solve puzzle" << std::endl;
    
    bool exit = false;
    while (window.isOpen())
    {
        //==========Loading============/
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
            }
        }
        //==============Drawing================//
        window.clear(sf::Color::White);
        drawBoard(&window, &sprites, &numbers);
        window.display();
    }
    textures.clear();
    sprites.clear();
    //=====================Finalizing=========================//
    return 0;
}
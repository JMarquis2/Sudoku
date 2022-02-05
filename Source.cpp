#include <SFML/Graphics.hpp>
//#include "solver.cpp"
//#include "DrawTextures.cpp"
#include <vector>
#include <cstdlib>
#include <stack>
#include <ctime>
#include <unordered_map>
#include <iostream>
#include "Tried.cpp"
using std::unordered_map;
using std::vector;
using std::stack;
struct hash_pair {
    template<class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};
int solvePuzzle(vector<vector<int>>* puzzle) {
    srand(time(NULL));
    int randI = rand() % 9;
    int randJ = rand() % 9;
    int indexI = randI;
    int indexJ = randJ;
    int guessesNeeded = 0;
    unordered_map<int, bool> possibilities;
    stack<std::pair<int, int>> guesses;
    unordered_map<std::pair<int, int>, unordered_map<int, bool>, hash_pair> alreadyTried;
    bool loopRow = true;
    bool loopCol = true;
    Tried* currTry = nullptr;
    //O(279)
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if ((*puzzle)[i][j] == -1)
                guessesNeeded++;
        }
    }

    while (loopRow) {
        //for (int i = randI; i < randI + 9; i++) {
            //int indexI = (i % 9);
            //O(81)
        while (loopCol) {
            //for (int j = randJ; j < randJ + 9; j++) {
                //int indexJ = (j % 9);
            if ((*puzzle)[indexI][indexJ] != -1) {
                indexJ = (indexJ + 1) % 9;
                if (indexJ == randJ)
                    break;
                continue;
            }
            for (int i = 0; i < 9; i++)
                possibilities[i + 1] = true;
            //O(9)
            //eliminates possible #s which share a row or column.
            for (int k = 0; k < 9; k++) {
                if ((*puzzle)[indexI][k] != -1)
                    possibilities.erase((*puzzle)[indexI][k]);
                if ((*puzzle)[k][indexJ] != -1)
                    possibilities.erase((*puzzle)[k][indexJ]);
            }
            //O(9)
            //eliminates possible #s which share a group.
            for (int l = indexI; l < indexI + 3; l++) {
                int indexL = (indexI / 3) * 3 + (l % 3);
                for (int m = indexJ; m < indexJ + 3; m++) {
                    int indexM = (indexJ / 3) * 3 + (m % 3);
                    if ((*puzzle)[indexL][indexM] != -1)
                        possibilities.erase((*puzzle)[indexL][indexM]);
                }

            }
            /*
            for (auto it = alreadyTried[std::make_pair(indexI, indexJ)].begin(); it != alreadyTried[std::make_pair(indexI, indexJ)].end(); it++) {
                if (it->second == true)
                    possibilities.erase(it->first);

            }
            */
            if (currTry) {
                for (auto it = currTry->impossible.begin(); it != currTry->impossible.end(); it++)
                    possibilities.erase(it->first);
            }
            //if possibilities is empty, backtrack. (pop stack and set indexI, indexJ to proper values associated with the stack. Also reset value of space.)
            //PROBLEM!!! when I back-track, I put my current guess as "already tried" but that guess may actually be CORRECT (it was a previous guess that did me in.) So, I need to figure out how to 
            //only "already tried" the problematic guess. Might need to use a tree of already-trieds (which would be straight cancer, especially when run on an empty board). Perhaps make a tree of guesses
            //in which 
            if (possibilities.size() == 0) {
                if (guesses.size() == 0)
                    return -1;
                //alreadyTried[guesses.top()][(*puzzle)[indexI][indexJ]] = true;
                currTry->root->impossible[(*puzzle)[guesses.top().first][guesses.top().second]] = true;
                Tried* tempTry = currTry->root;
                delete currTry;
                currTry = tempTry;
                (*puzzle)[guesses.top().first][guesses.top().second] = -1;
                indexI = guesses.top().first;
                indexJ = guesses.top().second;
                guesses.pop();
                continue;
            }

            //now, try random possibility. Record in stack.
             auto randomElement = possibilities.begin();
            for (int i = 0; i < (rand() % possibilities.size()); i++)
                randomElement++;
            (*puzzle)[indexI][indexJ] = randomElement->first;
            guesses.push(std::make_pair(indexI, indexJ));
            currTry = new Tried(currTry);

            //now, next iteration.

            indexJ = (indexJ + 1) % 9;
            if (indexJ == randJ)
                break;
        }
        indexI = (indexI + 1) % 9;
        if (guesses.size() == guessesNeeded) {
            while (currTry != nullptr) {
                Tried* tempTryPtr = currTry->root;
                delete tempTryPtr;
                currTry = tempTryPtr;
            }
            return 1;

        }
    }
    return 1;
}
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
                (*(*sprites)[(*numbers)[i][j]]).setPosition(sf::Vector2f(25 + 5 * (i/3) + 65 * i , 15 + 5 * (j / 3) + 65 * j));
                window->draw(*(*sprites)[(*numbers)[i][j]]);
            }
        }
    }
};

int main()
{
    //=============Initialization=============//
    sf::RenderWindow window(sf::VideoMode(610, 610), "Sudoku");
    window.setFramerateLimit(30);
    sf::Texture boardTexture;
    sf::Texture numOneTexture;
    sf::Texture numTwoTexture;
    sf::Texture numThreeTexture;
    sf::Texture numFourTexture;
    sf::Texture numFiveTexture;
    sf::Texture numSixTexture;
    sf::Texture numSevenTexture;
    sf::Texture numEightTexture;
    sf::Texture numNineTexture;
    numOneTexture.loadFromFile("1_9 Digits.png", sf::IntRect(0, 0, 35, 50));
    numTwoTexture.loadFromFile("1_9 Digits.png", sf::IntRect(35, 0, 35, 50));
    numThreeTexture.loadFromFile("1_9 Digits.png", sf::IntRect(70, 0, 35, 50));
    numFourTexture.loadFromFile("1_9 Digits.png", sf::IntRect(105, 0, 35, 50));
    numFiveTexture.loadFromFile("1_9 Digits.png", sf::IntRect(140, 0, 35, 50));
    numSixTexture.loadFromFile("1_9 Digits.png", sf::IntRect(175, 0, 35, 50));
    numSevenTexture.loadFromFile("1_9 Digits.png", sf::IntRect(210, 0, 35, 50));
    numEightTexture.loadFromFile("1_9 Digits.png", sf::IntRect(245, 0, 35, 50));
    numNineTexture.loadFromFile("1_9 Digits.png", sf::IntRect(280, 0, 35, 50));
    boardTexture.loadFromFile("board.png");
    std::vector<sf::Sprite*> sprites;
    sf::Sprite board(boardTexture);
    sprites.push_back(&board);
    sf::Sprite one(numOneTexture);
    sprites.push_back(&one);
    sf::Sprite two(numTwoTexture);
    sprites.push_back(&two);
    sf::Sprite three(numThreeTexture);
    sprites.push_back(&three);
    sf::Sprite four(numFourTexture);
    sprites.push_back(&four);
    sf::Sprite five(numFiveTexture);
    sprites.push_back(&five);
    sf::Sprite six(numSixTexture);
    sprites.push_back(&six);
    sf::Sprite seven(numSevenTexture);
    sprites.push_back(&seven);
    sf::Sprite eight(numEightTexture);
    sprites.push_back(&eight);
    sf::Sprite nine(numNineTexture);
    sprites.push_back(&nine);

    std::vector<std::vector<int>> numbers;
    std::string example = "030000400000043602050001000060000074070000030509000000007009360100206090000070000";

    for (int i = 0; i < 9; i++){
        std::vector<int> ones(9, i+1);
        numbers.push_back(ones);
    }
    /*
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            numbers[i][j] = (i + j) % 9 + 1;
        }
    }
    */
    int i = 0;
    for (int j = 0; j < 81; j++) {
        numbers[i][j / 9] = example[j] - 48;
        if (numbers[i][j / 9] == 0)
            numbers[i][j / 9] = -1;
        i = (i + 1) % 9;
    }
    
    //if (solvePuzzle(&numbers) == -1) std::cout << "error in solve puzzle" << std::endl;
    
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
    //=====================Finalizing=========================//
    return 0;
}
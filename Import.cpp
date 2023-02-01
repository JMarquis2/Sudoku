#include "Import.h"
void importSpritesFromFiles(std::vector<sf::Texture>* textures, std::vector<sf::Sprite*>* sprites) {

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
    textures->at(0).loadFromFile("board.png");
    textures->at(1).loadFromFile("1_9 Digits.png", sf::IntRect(0, 0, 35, 50));
    textures->at(2).loadFromFile("1_9 Digits.png", sf::IntRect(35, 0, 35, 50));
    textures->at(3).loadFromFile("1_9 Digits.png", sf::IntRect(70, 0, 35, 50));
    textures->at(4).loadFromFile("1_9 Digits.png", sf::IntRect(105, 0, 35, 50));
    textures->at(5).loadFromFile("1_9 Digits.png", sf::IntRect(140, 0, 35, 50));
    textures->at(6).loadFromFile("1_9 Digits.png", sf::IntRect(175, 0, 35, 50));
    textures->at(7).loadFromFile("1_9 Digits.png", sf::IntRect(210, 0, 35, 50));
    textures->at(8).loadFromFile("1_9 Digits.png", sf::IntRect(245, 0, 35, 50));
    textures->at(9).loadFromFile("1_9 Digits.png", sf::IntRect(280, 0, 35, 50));

    for (int i = 0; i < 10; i++) {
        sf::Sprite* tempSprite = new sf::Sprite(textures->at(i));
        sprites->push_back(tempSprite);
    }
}

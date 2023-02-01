#include "Solves.h"
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include "PairHash.h"
#include "DrawBoard.h"
int solvePuzzle(std::vector<std::vector<int>>* puzzle) {
    srand(time(NULL));
    int randI = rand() % 9;
    int randJ = rand() % 9;
    int indexI = randI;
    int indexJ = randJ;
    int guessesNeeded = 0;
    std::unordered_set<int> possibilities;
    std::stack<std::pair<int, int>> guesses;
    std::unordered_map<std::pair<int, int>, std::unordered_set<int>, hash_pair> impossible;
    bool loopRow = true;
    bool loopCol = true;
    //O(279)
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if ((*puzzle)[i][j] == -1)
                guessesNeeded++;
        }
    }
    while (loopRow) {
        //O(81)
        while (loopCol) {
            if ((*puzzle)[indexI][indexJ] != -1) {
                indexJ = (indexJ + 1) % 9;
                if (indexJ == randJ)
                    break;
                continue;
            }
            for (int i = 0; i < 9; i++)
                possibilities.insert(i + 1);
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
            if (impossible.count(std::make_pair(indexI, indexJ))) {
                for (auto it = impossible[std::make_pair(indexI, indexJ)].begin(); it != impossible[std::make_pair(indexI, indexJ)].end(); it++) {
                    possibilities.erase(*it);
                }
            }
            //if possibilities is empty, backtrack. (pop stack and set indexI, indexJ to proper values associated with the stack. Also reset value of space.)
            //PROBLEM!!! when I back-track, I put my current guess as "already tried" but that guess may actually be CORRECT (it was a previous guess that did me in.) So, I need to figure out how to 
            //only "already tried" the problematic guess. Might need to use a tree of already-trieds (which would be straight cancer, especially when run on an empty board). Perhaps make a tree of guesses
            //in which 
            if (possibilities.size() == 0) {
                if (guesses.size() == 0)
                    return -1;
                impossible[guesses.top()].insert((*puzzle)[guesses.top().first][guesses.top().second]);
                //make it so that it deletes this set, not just clears it (looks cleaner when debugging)
                if (impossible.count(std::make_pair(indexI, indexJ)))
                    impossible[std::make_pair(indexI, indexJ)].clear();
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
            (*puzzle)[indexI][indexJ] = *randomElement;
            guesses.push(std::make_pair(indexI, indexJ));

            //now, next iteration.
            indexJ = (indexJ + 1) % 9;
            if (indexJ == randJ)
                break;
        }
        indexI = (indexI + 1) % 9;
        //clean up
        if (guesses.size() == guessesNeeded) {
            return 1;

        }
    }
    return 1;
}
int improvedSolvePuzzle(std::vector<std::vector<int>>* puzzle) {
    srand(time(NULL));
    int randI = rand() % 9;
    int randJ = rand() % 9;
    int indexI = randI;
    int indexJ = randJ;
    int guessesNeeded = 0;
    std::unordered_set<int> possibilities;
    std::stack<std::pair<int, int>> guesses;
    std::unordered_map<std::pair<int, int>, std::unordered_set<int>, hash_pair> impossible;
    bool loopRow = true;
    bool loopCol = true;
    bool preScan = true;
    int resetCounter = 81;
    std::pair<int, int> start = std::make_pair(0, 0);
    int lowestPossibilities = 10;
    //O(279)
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if ((*puzzle)[i][j] == -1)
                guessesNeeded++;
        }
    }
    while (preScan) {
        //O(81)
        while (loopCol) {
            if ((*puzzle)[indexI][indexJ] != -1) {
                indexJ = (indexJ + 1) % 9;
                resetCounter--;
                if (indexJ == randJ)
                    break;
                continue;
            }
            for (int i = 0; i < 9; i++)
                possibilities.insert(i + 1);
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
            //if possibilities is empty, backtrack. (pop stack and set indexI, indexJ to proper values associated with the stack. Also reset value of space.)
            //PROBLEM!!! when I back-track, I put my current guess as "already tried" but that guess may actually be CORRECT (it was a previous guess that did me in.) So, I need to figure out how to 
            //only "already tried" the problematic guess. Might need to use a tree of already-trieds (which would be straight cancer, especially when run on an empty board). Perhaps make a tree of guesses
            //in which 
            if (possibilities.size() == 0) {
                return -1;
            }
            if (possibilities.size() == 1) {
                (*puzzle)[indexI][indexJ] = *possibilities.begin();
                if (indexI == start.first && indexJ == start.second) {
                    lowestPossibilities = 10;
                }
                guessesNeeded--;
                resetCounter = 81;
            }
            if (possibilities.size() > 1 && (possibilities.size() < lowestPossibilities)) {
                start.first = indexI;
                start.second = indexJ;
            }
            if (resetCounter < 0) {
                preScan = false;
                break;
            }
            //now, next iteration.
            indexJ = (indexJ + 1) % 9;
            resetCounter--;
            if (indexJ == randJ)
                break;
        }
        indexI = (indexI + 1) % 9;
        //clean up
        if (guessesNeeded == 0) {
            return 1;
        }
    }
    indexI = start.first;
    indexJ = start.second;
    while (loopRow) {
        //O(81)
        while (loopCol) {
            if ((*puzzle)[indexI][indexJ] != -1) {
                indexJ = (indexJ + 1) % 9;
                if (indexJ == start.second)
                    break;
                continue;
            }
            for (int i = 0; i < 9; i++)
                possibilities.insert(i + 1);
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
            if (impossible.count(std::make_pair(indexI, indexJ))) {
                for (auto it = impossible[std::make_pair(indexI, indexJ)].begin(); it != impossible[std::make_pair(indexI, indexJ)].end(); it++) {
                    possibilities.erase(*it);
                }
            }
            //if possibilities is empty, backtrack. (pop stack and set indexI, indexJ to proper values associated with the stack. Also reset value of space.)
            //PROBLEM!!! when I back-track, I put my current guess as "already tried" but that guess may actually be CORRECT (it was a previous guess that did me in.) So, I need to figure out how to 
            //only "already tried" the problematic guess. Might need to use a tree of already-trieds (which would be straight cancer, especially when run on an empty board). Perhaps make a tree of guesses
            //in which 
            if (possibilities.size() == 0) {
                if (guesses.size() == 0)
                    return -1;
                impossible[guesses.top()].insert((*puzzle)[guesses.top().first][guesses.top().second]);
                //make it so that it deletes this set, not just clears it (looks cleaner when debugging)
                if (impossible.count(std::make_pair(indexI, indexJ)))
                    impossible[std::make_pair(indexI, indexJ)].clear();
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
            (*puzzle)[indexI][indexJ] = *randomElement;
            guesses.push(std::make_pair(indexI, indexJ));

            //now, next iteration.
            indexJ = (indexJ + 1) % 9;
            if (indexJ == start.second)
                break;
        }
        indexI = (indexI + 1) % 9;
        //clean up
        if (guesses.size() == guessesNeeded) {
            return 1;

        }
    }
    return 1;
}
int improvedSolvePuzzleInSteps(std::vector<std::vector<int>>* puzzle, sf::RenderWindow* window, std::vector<sf::Sprite*>* sprites) {
    srand(time(NULL));
    int randI = rand() % 9;
    int randJ = rand() % 9;
    int indexI = randI;
    int indexJ = randJ;
    int guessesNeeded = 0;
    std::unordered_set<int> possibilities;
    std::stack<std::pair<int, int>> guesses;
    std::unordered_map<std::pair<int, int>, std::unordered_set<int>, hash_pair> impossible;
    bool loopRow = true;
    bool loopCol = true;
    bool preScan = true;
    int resetCounter = 81;
    std::pair<int, int> start = std::make_pair(0, 0);
    int lowestPossibilities = 10;
    int display = 0;
    //O(279)
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if ((*puzzle)[i][j] == -1)
                guessesNeeded++;
        }
    }
    while (preScan) {
        //O(81)
        while (loopCol) {
            if ((*puzzle)[indexI][indexJ] != -1) {
                indexJ = (indexJ + 1) % 9;
                resetCounter--;
                if (indexJ == randJ)
                    break;
                continue;
            }
            for (int i = 0; i < 9; i++)
                possibilities.insert(i + 1);
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
            //if possibilities is empty, backtrack. (pop stack and set indexI, indexJ to proper values associated with the stack. Also reset value of space.)
            //PROBLEM!!! when I back-track, I put my current guess as "already tried" but that guess may actually be CORRECT (it was a previous guess that did me in.) So, I need to figure out how to 
            //only "already tried" the problematic guess. Might need to use a tree of already-trieds (which would be straight cancer, especially when run on an empty board). Perhaps make a tree of guesses
            //in which 
            if (possibilities.size() == 0) {
                return -1;
            }
            if (possibilities.size() == 1) {
                (*puzzle)[indexI][indexJ] = *possibilities.begin();
                if (indexI == start.first && indexJ == start.second) {
                    lowestPossibilities = 10;
                }
                guessesNeeded--;
                resetCounter = 81;
                drawBoard(window, sprites, puzzle);
                window->display();
            }
            if (possibilities.size() > 1 && (possibilities.size() < lowestPossibilities)) {
                start.first = indexI;
                start.second = indexJ;
            }
            if (resetCounter < 0) {
                preScan = false;
                break;
            }
            //now, next iteration.
            indexJ = (indexJ + 1) % 9;
            resetCounter--;
            if (indexJ == randJ)
                break;
        }
        indexI = (indexI + 1) % 9;
        //clean up
        if (guessesNeeded == 0) {
            return 1;
        }
    }
    indexI = start.first;
    indexJ = start.second;
    while (loopRow) {
        //O(81)
        while (loopCol) {
            if ((*puzzle)[indexI][indexJ] != -1) {
                indexJ = (indexJ + 1) % 9;
                if (indexJ == start.second)
                    break;
                continue;
            }
            for (int i = 0; i < 9; i++)
                possibilities.insert(i + 1);
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
            if (impossible.count(std::make_pair(indexI, indexJ))) {
                for (auto it = impossible[std::make_pair(indexI, indexJ)].begin(); it != impossible[std::make_pair(indexI, indexJ)].end(); it++) {
                    possibilities.erase(*it);
                }
            }
            //if possibilities is empty, backtrack. (pop stack and set indexI, indexJ to proper values associated with the stack. Also reset value of space.)
            //PROBLEM!!! when I back-track, I put my current guess as "already tried" but that guess may actually be CORRECT (it was a previous guess that did me in.) So, I need to figure out how to 
            //only "already tried" the problematic guess. Might need to use a tree of already-trieds (which would be straight cancer, especially when run on an empty board). Perhaps make a tree of guesses
            //in which 
            if (possibilities.size() == 0) {
                if (guesses.size() == 0)
                    return -1;
                impossible[guesses.top()].insert((*puzzle)[guesses.top().first][guesses.top().second]);
                //make it so that it deletes this set, not just clears it (looks cleaner when debugging)
                if (impossible.count(std::make_pair(indexI, indexJ)))
                    impossible[std::make_pair(indexI, indexJ)].clear();
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
            (*puzzle)[indexI][indexJ] = *randomElement;
            guesses.push(std::make_pair(indexI, indexJ));

            //draw & display
            if (display++ == 75) {
                drawBoard(window, sprites, puzzle);
                window->display();
                display = 0;
            }

            //now, next iteration.
            indexJ = (indexJ + 1) % 9;
            if (indexJ == start.second)
                break;
        }
        indexI = (indexI + 1) % 9;
        //clean up
        if (guesses.size() == guessesNeeded) {
            return 1;

        }
    }
    return 1;
}
int solvePuzzleInSteps(std::vector<std::vector<int>>* puzzle, sf::RenderWindow* window, std::vector<sf::Sprite*>* sprites) {
    srand(time(NULL));
    int randI = rand() % 9;
    int randJ = rand() % 9;
    int indexI = randI;
    int indexJ = randJ;
    int guessesNeeded = 0;
    std::unordered_set<int> possibilities;
    std::stack<std::pair<int, int>> guesses;
    std::unordered_map<std::pair<int, int>, std::unordered_set<int>, hash_pair> impossible;
    bool loopRow = true;
    bool loopCol = true;
    int display = 0;
    //O(279)
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if ((*puzzle)[i][j] == -1)
                guessesNeeded++;
        }
    }
    while (loopRow) {
        //O(81)
        while (loopCol) {
            if ((*puzzle)[indexI][indexJ] != -1) {
                indexJ = (indexJ + 1) % 9;
                if (indexJ == randJ)
                    break;
                continue;
            }
            for (int i = 0; i < 9; i++)
                possibilities.insert(i + 1);
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
            if (impossible.count(std::make_pair(indexI, indexJ))) {
                for (auto it = impossible[std::make_pair(indexI, indexJ)].begin(); it != impossible[std::make_pair(indexI, indexJ)].end(); it++) {
                    possibilities.erase(*it);
                }
            }
            //if possibilities is empty, backtrack. (pop stack and set indexI, indexJ to proper values associated with the stack. Also reset value of space.)
            //PROBLEM!!! when I back-track, I put my current guess as "already tried" but that guess may actually be CORRECT (it was a previous guess that did me in.) So, I need to figure out how to 
            //only "already tried" the problematic guess. Might need to use a tree of already-trieds (which would be straight cancer, especially when run on an empty board). Perhaps make a tree of guesses
            //in which 
            if (possibilities.size() == 0) {
                if (guesses.size() == 0)
                    return -1;
                impossible[guesses.top()].insert((*puzzle)[guesses.top().first][guesses.top().second]);
                //make it so that it deletes this set, not just clears it (looks cleaner when debugging)
                if (impossible.count(std::make_pair(indexI, indexJ)))
                    impossible[std::make_pair(indexI, indexJ)].clear();
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
            (*puzzle)[indexI][indexJ] = *randomElement;
            guesses.push(std::make_pair(indexI, indexJ));
            if (display++ == 180) {
                display = 0;
                drawBoard(window, sprites, puzzle);
                window->display();
            }


            //now, next iteration.
            indexJ = (indexJ + 1) % 9;
            if (indexJ == randJ) {
                //drawBoard(window, sprites, puzzle);
                //window->display();
                break;
            }
        }
        indexI = (indexI + 1) % 9;
        //clean up
        if (guesses.size() == guessesNeeded) {
            return 1;

        }
    }
    return 1;
}
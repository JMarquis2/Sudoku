/*#include <vector>
#include <cstdlib>
#include <stack>
#include <ctime>
#include <unordered_map>
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
		while(loopCol){
		//for (int j = randJ; j < randJ + 9; j++) {
			//int indexJ = (j % 9);
			if ((*puzzle)[indexI][indexJ] != -1)
				continue;
			for (int i = 0; i < 9; i++)
				possibilities[i + 1] = true;
			//O(9)
			//eliminates possible #s which share a row or column.
			for (int k = 0; k < 9; k++) {
				if((*puzzle)[indexI][k] != -1)
					possibilities.erase((*puzzle)[indexI][k]);
				if ((*puzzle)[k][indexJ] != -1)
					possibilities.erase((*puzzle)[k][indexJ]);
			}
			//O(9)
			//eliminates possible #s which share a group.
			for(int l = indexI; l < indexI + 3; l++){
				int indexL = (indexI / 3) * 3 + (l % 3);
				for (int m = indexJ; m < indexJ + 3; m++) {
					int indexM = (indexJ / 3) * 3 + (m % 3);
					if((*puzzle)[indexL][indexM] != -1)
						possibilities.erase((*puzzle)[indexL][indexM]);
				}
					
			}
			for (auto it = alreadyTried[std::make_pair(indexI, indexJ)].begin(); it != alreadyTried[std::make_pair(indexI, indexJ)].end(); it++) {
				if (it->second == true)
					possibilities.erase(it->first);

			}
			//if possibilities is empty, backtrack. (pop stack and set indexI, indexJ to proper values associated with the stack. Also reset value of space.)
			if (possibilities.size() == 0) {
				if (guesses.size() == 0)
					return -1;
				alreadyTried[guesses.top()][(*puzzle)[indexI][indexJ]] = true;
				(*puzzle)[guesses.top().first][guesses.top().second] = -1;
				guesses.pop();
				indexI = guesses.top().first;
				indexJ = guesses.top().second - 1;
				if ((indexJ + 1) % 9 == randJ)
					indexI--;
			}

			//now, try random possibility. Record in stack.
			auto randomElement = possibilities.begin();
			for (int i = 0; i < (rand() % possibilities.size()); i++)
				randomElement++;
			(*puzzle)[indexI][indexJ] = randomElement->first;
			guesses.push(std::make_pair(indexI, indexJ));

			//now, next iteration.
			
			indexJ = (indexJ + 1) % 9;
			if (indexJ == randJ)
				break;
		}
		indexI = (indexI + 1) % 9;
		if (guesses.size() == guessesNeeded)
			return 1;
			break;
	}
	return 1;
}
*/
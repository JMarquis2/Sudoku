#pragma once
#include <unordered_map>
struct Tried
{
	std::unordered_map<int, bool> impossible;
	Tried* root;
	Tried() {
		root = nullptr;
	}
	Tried(Tried* root) {
		this->root = root;
	}
	~Tried() {
		impossible.clear();
	}
};
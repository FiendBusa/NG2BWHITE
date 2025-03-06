#include "pch.h"
#include "functions.h"
#include <random>
#include <cstddef>
#include "globals.h"
#include <vector>
#include <iterator>
#include <random>


std::random_device rd;
std::mt19937 gen(rd());


bool HPMatch(const int* hpArray, size_t size, int hpToMatch) {

	for (int i = 0; i < size; i++) {
		if (hpArray[i] == hpToMatch) { return true; }
	}
	return false;
}
void AssignHPoolVector(const int* hpArray, size_t size, std::vector<int>& vec) {
	vec.clear();
	vec.reserve(size);
	std::copy(hpArray, hpArray + size, std::back_inserter(vec));
}
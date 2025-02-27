#include "../include/utils.hpp"
#include <random>

void clearscreen() {
    #ifdef _WIN32
		std::system("cls");
    #else
        std::system("clear");
    #endif
}

int Random(const int& inferiorLimit, const int& superiorLimit) {

	static std::random_device rd;  // Obtain a random seed from hardware
	static std::mt19937 gen(rd()); // Initialize Mersenne Twister PRNG
	static std::uniform_int_distribution<int> dist(0, superiorLimit); // Inclusive Range [a, b]

	return dist(gen);
}

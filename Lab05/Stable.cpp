#include <iostream>
#include <string>
#include "Stable.h"
#include "Horse.h"

using namespace std;


Stable::Stable() {
	// Constructor for Stable
	// horsesInStable[0] = Horse();
	currentHorseNum = 0;
}

void Stable::addHorse(Horse* h) {
	// Adds horse to the stable
	if (currentHorseNum < maxHorses) {
		horsesInStable[currentHorseNum] = *h;
		currentHorseNum++;
	}
	else {
		throw FullStable(currentHorseNum + 1);
	}

}

Horse Stable::removeHorse() {
	// Removes horse from the stable
	if (currentHorseNum > 0) {
		currentHorseNum--;
		return horsesInStable[currentHorseNum];
	}
	else {
		throw EmptyStable();
	}

}

int Stable::getHorseNum() {
	// Returns the number of horses in the stable
	return currentHorseNum;
}

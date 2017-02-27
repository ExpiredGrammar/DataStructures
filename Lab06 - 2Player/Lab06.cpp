#include <iostream>
#include <string>
#include "Stack.h"

using namespace std;

struct Disk {
	int diskNum;
	string color;
};
void displayTowers(Stack<Disk> &l, Stack<Disk> &m, Stack<Disk> &r, int size) { //size is numDisks

																			   // adds first line
	string t = "\t|\t|\t|";
	string ls, ms, rs;

	// gets the appropriate values from the stack
	// if it is a nullptr make it a | 
	for (int i = size - 1; i >= 0; i--) {
		if (getItem(l, i) == nullptr) { // || getItem(l, i) == 0
			ls = "|";
		}
		else {
			ls = to_string((*getItem(l, i)).diskNum) + " " + (*getItem(l, i)).color;
		}
		if (getItem(m, i) == nullptr) {
			ms = "|";
		}
		else {
			ms = to_string((*getItem(m, i)).diskNum) + " " + (*getItem(m, i)).color;
		}
		if (getItem(r, i) == nullptr) {
			rs = "|";
		}
		else {
			rs = to_string((*getItem(r, i)).diskNum) + " " + (*getItem(r, i)).color;
		}
		t += "\n\t" + ls + "\t" + ms + "\t" + rs;
	}
	// adds base plus options
	t += "\n    -------------------------";
	t += "\n    |  (1)     (2)     (3)  |";
	t += "\n    -------------------------\n";

	// print the board
	cout << t;
}

int changePlayer(int playerNum) {
	if(playerNum == 0){ return 1; }
	else { return 0; }
}

int main() {
	cout << "Welcome to Towers of Hanoi!" << endl << endl;
	int numDisks;

	// Choose number of disks.
	do { 
		cout << "Players, how many disks would you like to use?: ";
		cin >> numDisks;
		if (numDisks < 1) {
			cout << "Please choose a positive number of disks" << endl;
		}
	} while (numDisks < 1);

	// make 3 stacks, one for each tower
	Stack<Disk> lTower = Stack<Disk>(numDisks);
	Stack<Disk> mTower = Stack<Disk>(numDisks);
	Stack<Disk> rTower = Stack<Disk>(numDisks);
	// Make tower to check for a win.
	Stack<Disk> possibleWinTower = Stack<Disk>(numDisks);

	// makes a pointer array of disks, and pushes it to the left tower
	Disk *disks = new Disk[numDisks];
	Disk *disks2 = new Disk[numDisks];
	for (int i = numDisks; i > 0; i--) {
		disks[i - 1].diskNum = i; // fill the disk array
		disks[i - 1].color = "Blue";
		lTower.push(&disks[i - 1]); // push the disk to the left tower
	}
	for (int i = numDisks; i > 0; i--) {
		disks2[i - 1].diskNum = i;
		disks2[i - 1].color = "Red ";
		rTower.push(&disks2[i - 1]);
	}

	bool stillPlaying = true;
	int tower;
	Stack<Disk>* fromTower; // the tower the disk comes from
	Stack<Disk>* toTower; // the tower the disk goes
	string playerColors[] = {"Blue", "Red "};
	Stack<Disk>* winningTowers[2] = {&rTower, &lTower};
	string winner;
	int currentPlayer = 0;
	bool invalidTower = false;
	while (stillPlaying) {

		cout << endl;
		cout << "Player " << currentPlayer + 1 << " is playing. Their color is " << playerColors[currentPlayer] << endl;
		displayTowers(lTower, mTower, rTower, numDisks);
		
		// Check if any move is available for the player
		if (!lTower.isEmpty() && !mTower.isEmpty() && rTower.isEmpty()) {
			if ((lTower.top()->color != playerColors[currentPlayer]) && (mTower.top()->color != playerColors[currentPlayer])) {
				cout << "You have no possible moves." << endl;
				currentPlayer = changePlayer(currentPlayer);
				continue;
			}
		}
		else if (!lTower.isEmpty() && mTower.isEmpty() && !rTower.isEmpty()) {
			if ((lTower.top()->color != playerColors[currentPlayer]) && (rTower.top()->color != playerColors[currentPlayer])) {
				cout << "You have no possible moves." << endl;
				currentPlayer = changePlayer(currentPlayer);
				continue;
			}
		}
		else if (lTower.isEmpty() && !mTower.isEmpty() && !rTower.isEmpty()) {
			if ((mTower.top()->color != playerColors[currentPlayer]) && (rTower.top()->color != playerColors[currentPlayer])) {
				cout << "You have no possible moves." << endl;
				currentPlayer = changePlayer(currentPlayer);
				continue;
			}
		}
		else if (!lTower.isEmpty() && !mTower.isEmpty() && !rTower.isEmpty()) {
			if ((lTower.top()->color != playerColors[currentPlayer]) && (mTower.top()->color != playerColors[currentPlayer]) && (rTower.top()->color != playerColors[currentPlayer])) {
				cout << "You have no possible moves." << endl;
				currentPlayer = changePlayer(currentPlayer);
				continue;
			}
		}
		
		// Pick up the disk
		do {
			invalidTower = false;
			cout << "Choose the tower you would like to pick from: ";
			cin >> tower;
			try {
				switch (tower) {
				case 1:
					fromTower = &lTower;
					break;
				case 2:
					fromTower = &mTower;
					break;
				case 3:
					fromTower = &rTower;
					break;
				default:
					cout << "Choose a valid tower" << endl;
					invalidTower = true; // restart the loop
					break;
				}
				// Make sure the player's disk is being moved
				if (!fromTower->isEmpty()) {
					if ((fromTower->top()->color) != (playerColors[currentPlayer])) {
						cout << "You cannot move another player's disks. Please choose another tower." << endl;
						invalidTower=true;
					}
				}
				else { // Makes sure the tower has a disk to move
					cout << "That tower is empty. Choose another tower." << endl;
					invalidTower=true;
				}				
			}
			catch (Stack<int>::StackUnderflow) { // if the tower is empty, tell the user
				cout << "This tower is empty, there are no disks to pick up" << endl;
				invalidTower=true;
			}
		}while (invalidTower);

		// Put down the disk
		
		do {
			invalidTower = false;
			cout << "Choose the tower you would like to place the disk: ";
			cin >> tower;
			switch (tower) {
			case 1:
				toTower = &lTower;
				break;
			case 2:
				toTower = &mTower;
				break;
			case 3:
				toTower = &rTower;
				break;
			default:
				cout << "Choose a valid tower" << endl;
				invalidTower = true;
				break;
			}
			if (toTower->isFull() || (toTower == fromTower)) { // Checks for valid moves so that the disk is not moved to the same tower or to a full tower
				cout << "Please choose a valid tower that is not full and is not the same as the earlier tower." << endl;
				invalidTower = true; 
			}
		} while (invalidTower);

		// Moves disk
		if (toTower->isEmpty()) { // if toTower is empty, put the disk there
			toTower->push(fromTower->pop());
			// TODO Task 4: log move
		}
		else if (fromTower->top()->diskNum > toTower->top()->diskNum) {
			cout << "That's an illegal move. You have lost your turn." << endl;
		}
		else { // the last scenario is when you take a disk from a tower and put it on a non empty tower
			toTower->push(fromTower->pop());
			// TODO Task 4: log move
		}
		
		// Checks for win if the player's winning tower is full
		if ( winningTowers[currentPlayer]->isFull() ) {
			bool won = true;
			for (int i = 0; i < numDisks; i++) { // Move disks to another tower to check if they all have the same color
				fromTower = winningTowers[currentPlayer];
				toTower = &possibleWinTower;
				toTower->push(fromTower->pop());
				cout << toTower->top()->color << " " << toTower->top()->diskNum << endl;
				if ((toTower->top()->color) != (playerColors[currentPlayer])) { won = false; } // Set flag for won false if the disks in the tower do not have the same color
			}
			for (int i = 0; i < numDisks; i++) { // Move the disks back to the original tower after checking
				fromTower = &possibleWinTower;
				toTower = winningTowers[currentPlayer];
				toTower->push(fromTower->pop());
			}
			if (won) { // If the player has won, set the winner and exit
				winner = playerColors[currentPlayer];
				stillPlaying = false;				
			}					
		}
		currentPlayer = changePlayer(currentPlayer); // Change the current player
	} while (stillPlaying);
	int a;
	cout << "Congratulations " << winner << " has won!" << endl;
	displayTowers(lTower, mTower, rTower, numDisks);
	cin >> a;
}
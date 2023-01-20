/**
*
* Solution to course project # 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Diana Pantova
* @idnumber 7MI0600233
* @compiler VC
*
* <main .cpp file>
*
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "global-constants.h"
#include "text-editing.h"
#include "level-descriptions.h"
#include "file-helper.h"
#include "print-helper.h"
#include "helper-functions.h"

size_t startingMenu(char* input)
{
	bool incorrectInput = false;
	
	do {
		printStartingMenu(incorrectInput);
		std::cin.getline(input, MAX_INPUT_SIZE);

		if (input[1] == '\0') {
			switch (input[0]) {
			case '1':
				return login;
			case '2':
				return signup;
			case '3':
				return quit;
			default:
				break;
			}
		}
		incorrectInput = true;
		clearConsole();
		
	} while (true);
}

size_t loginMenu(char* input)
{
	char filePath[MAX_INPUT_SIZE] = {};
	printLoginMenu();
	
	if (!loginUsername(input, filePath)) {
		return stMenu;
	}
	
	if (!loginPassword(input, filePath)) {
		return stMenu;
	}

	myStrCpy(input, filePath, MAX_INPUT_SIZE);

	return account;
}

size_t signupMenu(char* input)
{
	std::cout << "(Type 'b' to go back.)\n\n";
	std::cout << "Sign-up\n" << "Create a new account.\n\n";
	std::cout << CSI << "E" << "Password: " << CSI << "F";

	char filePath[MAX_INPUT_SIZE] = {};
	
	if (!createValidUsername(input, filePath)) {
		return stMenu;
	}

	std::ofstream newUser;
	if (!openAccount(filePath, newUser)) {
		return quit;
	}
	newUser << input << std::endl;
	int seed = createSeed(input);

	std::cout << CSI << "H" << CSI << "K"; // moves to first line and erases it
	std::cout << "(Cannot go back until account creation process is finished!)";
	std::cout << CSI << "6E"; // moves to current line
	
	createValidPass(input, "Password: ");

	defaultAccoutData(newUser, input, seed);
	newUser.close();

	successfulSignup(input);

	return stMenu;
}

void settingsMenu(char* input, std::fstream& account, char* filePath)
{
	bool incorrectInput;
	do {
		incorrectInput = false;
		printSettingsMenu(incorrectInput);
		std::cin.getline(input, MAX_INPUT_SIZE);

		if (input[1] == '\0') {
			switch (input[0]) {
			case 'b':
				return;
			case '1':
				changePassword(input, account, filePath);
				clearConsole();
				break;
			default:
				incorrectInput = true;
				break;
			}
		}
		else {
			incorrectInput = true;
		}
		clearConsole();

	} while (true);
}

bool game(char* input, std::fstream& account, char* filePath, const Level * pickedLvl)
{
	unsigned short currLives = 0;
	unsigned short currProg[MAX_LVL_SIZE][MAX_LVL_SIZE] = {};
	const Level * lvl = 
		(pickedLvl == nullptr) ? 
		pickCorrectLevel(input, account, currLives, currProg) 
		: pickedLvlData(pickedLvl, currLives, currProg);
	printBoard(lvl, currProg, currLives);
    
	Point A1, print;
	assignPointCoord(lvl, A1, print);
	bool goBack = false,
		validAction = true,
		alrMarked = false,
		correctGuess = true,
		alive = true,
		success = false,
		bigBoard = lvl->LEVEL > (NUM_OF_LVL - 2);

	do {
		printLastLines(validAction, correctGuess, alrMarked, currLives, print);
		validAction = true;
		correctGuess = true;
		alrMarked = false;

		std::cin.getline(input, MAX_INPUT_SIZE);

		if (input[0] == 'b' && input[1] == '\0') {
			goBack = true;
			break;
		}
		validAction = validGameAction(input, lvl, bigBoard);
		if (!validAction) {
			continue;
		}

		Point action = {};
		getActionCoord(action, input, bigBoard);
		if (currProg[action.y][action.x] != 2) {
			alrMarked = true;
			continue;
		}
		bool guess = getGuess(input, bigBoard);
		correctGuess = isCorrectGuess(action, guess, lvl);
		
		if (correctGuess) {
			currProg[action.y][action.x] = guess;
			if (updateBoard(action, currProg, lvl, A1)) {
				success = true;
			}
		}
		else {
			currLives--;
			alive = currLives > 0;
		}
	} while (!goBack && alive && !success);

	unsigned short result = assignResult(goBack, alive, success);
	if (!results(result, print, input, currLives, currProg, lvl, filePath, account)) {
		return false;
	}
	return true;
}

bool lvlProgCases(char* input, std::fstream& account, char* filePath, bool &incorrectInput)
{
	switch (input[0]) {
	case '1':
		clearConsole();
		getSpecifiedLine(FILE_LINE::lvl1, account, input, MAX_INPUT_SIZE);
		return game(input, account, filePath, listOfLevels(1, input[3] - '0'));
	case '2':
		clearConsole();
		getSpecifiedLine(FILE_LINE::lvl2, account, input, MAX_INPUT_SIZE);
		return game(input, account, filePath, listOfLevels(2, input[3] - '0'));
	case '3':
		clearConsole();
		getSpecifiedLine(FILE_LINE::lvl3, account, input, MAX_INPUT_SIZE);
		return game(input, account, filePath, listOfLevels(3, input[3] - '0'));;
	case '4':
		clearConsole();
		getSpecifiedLine(FILE_LINE::lvl4, account, input, MAX_INPUT_SIZE);
		return game(input, account, filePath, listOfLevels(4, input[3] - '0'));
	case '5':
		clearConsole();
		getSpecifiedLine(FILE_LINE::lvl5, account, input, MAX_INPUT_SIZE);
		return game(input, account, filePath, listOfLevels(5, input[3] - '0'));
	default:
		incorrectInput = true;
		return false;
	}
}

void levelProgressMenu(char* input, std::fstream& account, char* filePath)
{
	printLvlProgMenu(input, account);
	getSpecifiedLine(FILE_LINE::nextUnlocked, account, input, MAX_INPUT_SIZE);
	unsigned short maxUnlocked = input[0];
	
	bool incorrectInput = false;
	bool locked = false;
	do {
		if (incorrectInput) {
			std::cout << "Incorrect input! ";
		}
		else if (locked) {
			std::cout << "Level is locked! ";
		}
		std::cout << "Please type the level number you wish to play:\n";
		std::cin.getline(input, MAX_INPUT_SIZE);
		incorrectInput = false;

		if (input[1] == '\0') {
			if (input[0] == 'b') {
				return;
			}
			if (input[0] > maxUnlocked) {
				locked = true;
				std::cout << CSI << "2F" << CSI << "J";
				continue;
			}
			if (lvlProgCases(input, account, filePath, incorrectInput)) {
				return;
			}
		}
		else {
			incorrectInput = true;
		}
		std::cout << CSI << "2F" << CSI << "J";
	} while (true);
}

size_t accountMenu(char* input)
{
	std::fstream account;
	char filePath[MAX_INPUT_SIZE] = {};
	myStrCpy(filePath, input, MAX_INPUT_SIZE);

	if (!openAccount(filePath, account)) {
		return stMenu;
	}

	bool incorrectInput = false;

	while (account.is_open()) {
		printAccountMenu(input, account, incorrectInput);
		
		std::cin.getline(input, MAX_INPUT_SIZE);
		incorrectInput = false;
		
		if (input[1] == '\0') {
			clearConsole();
			switch (input[0]) {
			case '1':
				if (!game(input, account, filePath, nullptr)) {
					return quit;
				}
				break;
			case '2':
				levelProgressMenu(input, account, filePath);
				break;
			case '3':
				settingsMenu(input, account, filePath);
				break;
			case '4': // logout
				account.close();
				return stMenu;
			case '5': // exit
				account.close();
				return quit;
			default:
				incorrectInput = true;
				break;
			}
			clearConsole();
		}
		else {
			incorrectInput = true;
		}
	}

	clearConsole();
	std::cout << "Error! File crashed! Returning to main menu!\n\n";
	std::cout << "(Press enter to continue.)";
	char temp[2] = {};
	std::cin.getline(temp, 1);

	return stMenu;
}

int main()
{
	size_t select = stMenu;
	bool exitProgram = false;
	char input[MAX_INPUT_SIZE] = {};
	
	do {
		switch (select) {
		case stMenu:
			select = startingMenu(input);
			break;
		case login:
			select = loginMenu(input);
			break;
		case signup:
			select = signupMenu(input);
			break;
		case account:
			select = accountMenu(input);
			break;
		default:
			std::cout << "Error! Unknown selection! Please restart the program.";
			select = quit;
		}
		clearConsole();
	} while (select != quit);

	return 0;
}

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
#include "text-editing.h"
#include "global-constants.h"
#include "helper-functions.h"

size_t startingMenu(char* input)
{
	
	bool incorrectInput = false;
	
	do {
		// TODO: change printing style to new one
		printStartingMenu(incorrectInput);
		std::cin.getline(input, MAX_INPUT_SIZE);

		if (myStrLen(input) == 1) {
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
	std::cout << "\033[E" << "Password: " << "\033[F";

	char filePath[MAX_INPUT_SIZE] = {};
	
	if (!createValidUsername(input, filePath)) {
		return stMenu;
	}

	std::ofstream newUser(filePath);
	newUser << input << std::endl;

	std::cout << "\033[H\033[K"; // moves to first line and erases it
	std::cout << "(Cannot go back until account creation process is finished!)";
	std::cout << "\033[6E"; // moves to current line
	
	createValidPass(input);

	defaultAccoutData(newUser, input);
	newUser.close();

	successfulSignup(input);

	return stMenu;
}

//void settingsMenu(char* input, std::ifstream& accountRead, std::ofstream& accountWrite)
//{
//	
//}

size_t accountMenu(char* input)
{
	std::ifstream accountRead;
	std::ofstream accountWrite;
	if (!openAccount(input, accountRead, accountWrite)) {
		return stMenu;
	}

	printAccountMenu(input, accountRead);

	while (accountRead && accountWrite) {		
		std::cin.getline(input, MAX_INPUT_SIZE);

		if (myStrLen(input) == 1) {
			switch (input[0]) {
			case '1':
				//game
				break;
			case '2':
				//lvl progress
				break;
			case '3':
				//settings
				break;
			case '4': // logout
				accountRead.close();
				accountWrite.close();
				return stMenu;
			case '5': // exit
				accountRead.close();
				accountWrite.close();
				return quit;
			default:
				break;
			}
		}
		std::cout << "\033[9H\033[J";
		std::cout << "Incorrect input.\nPlease type a valid menu number:\n";
	}
}

int main()
{
	size_t select = stMenu;
	bool exitProgram = false;
	char input[MAX_INPUT_SIZE] = {};
	
	do {
		switch (select) {
		case quit:
			exitProgram = true;
			break;
		case stMenu:
			select = startingMenu(input);
			clearConsole();
			break;
		case login:
			select = loginMenu(input);
			clearConsole();
			break;
		case signup:
			select = signupMenu(input);
			clearConsole();
			break;
		case account:
			select = accountMenu(input);
			clearConsole();
			break;
		default:
			std::cout << "Error! Unknown selection! Please restart the program.";
			exitProgram = true;
		}
	} while (!exitProgram);

	return 0;
}

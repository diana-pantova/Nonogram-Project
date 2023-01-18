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

	return account;
}

size_t signupMenu(char* input)
{
	std::cout << "(Type 'b' to go back.)\n\n";
	std::cout << "Sign-up\n\n";

	char filePath[MAX_INPUT_SIZE] = {};
	
	if (!createValidUsername(input, filePath)) {
		clearConsole();
		return stMenu;
	}

	std::ofstream newUser(filePath);
	newUser << input << std::endl;

	clearConsole();

	std::cout << "Sign-up\n";
	std::cout << "Please finish the account creation process.\n\n";
	std::cout << "Username: " << input << std::endl;
	
	createValidPass(input);

	encrypt(input);
	newUser << input << std::endl;
	newUser.close();

	successfulSignup(input);

	return stMenu;
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
			std::cout << "Successfully logged in! Congrats!"; // placeholder
			exitProgram = true;
			break;
		default:
			std::cout << "Error! Unknown selection! Please restart the program.";
			exitProgram = true;
		}
	} while (!exitProgram);

	return 0;
}

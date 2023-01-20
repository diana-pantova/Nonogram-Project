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
* <header with helper functions for printing menus>
*
*/

#pragma once

inline void printStartingMenu(bool incorrectInput)
{
	std::cout << "Welcome to Nonogram!\n\n";
	std::cout << "1. Login\n";
	std::cout << "2. Sign-up\n";
	std::cout << "3. Exit\n\n";
	if (incorrectInput) {
		std::cout << "Incorrect input.\nPlease type a valid menu number:\n";
	}
	else {
		std::cout << "Please type a menu number:\n";
	}
}

inline void printLoginMenu()
{
	std::cout << "(Type 'b' to go back.)\n\n";
	std::cout << "Login\n" << "Log into an existing account.\n\n";
	std::cout << "\033[E" << "Password: " << "\033[F"; // moves cursor forward, prints, then back again
}

inline void printSettingsMenu(bool incorrectInput)
{
	std::cout << "(Type 'b' to go back.)\n\n";
	std::cout << "Settings\n\n";
	std::cout << "1. Change Password\n\n";
	if (incorrectInput) {
		std::cout << "Incorrect input.\nPlease type a valid menu number:\n";
	}
	else {
		std::cout << "Please type a menu number:\n";
	}
}

inline void successfulSignup(char* input)
{
	clearConsole();
	std::cout << "Account successfully created!\n";
	std::cout << "You can now log in from the Login Menu.\n";
	std::cout << "Enjoy!\n\n";

	std::cout << "(Press Enter to continue.)\n";
	std::cin.getline(input, 1);
}

inline void printAccountMenu(char* input, std::fstream& account, bool incorrectInput)
{
	std::cout << "Welcome, ";
	getSpecifiedLine(FILE_LINE::name, account, input, MAX_INPUT_SIZE);
	std::cout << input << "!\n\n";

	getSpecifiedLine(FILE_LINE::curLvl, account, input, MAX_INPUT_SIZE);
	char curLvl = input[0];
	getSpecifiedLine(FILE_LINE::nextUnlocked, account, input, MAX_INPUT_SIZE);
	char next = input[0];
	if (curLvl == '0') {
		if (next == '1') {
			std::cout << "1. New Game\n";
		}
		else {
			std::cout << "1. Next Level\n";
		}
	}
	else {
		std::cout << "1. Continue Game\n";
	}
	std::cout << "2. Level Progress\n";
	std::cout << "3. Settings\n";
	std::cout << "4. Log out\n";
	std::cout << "5. Exit\n\n";

	if (incorrectInput) {
		std::cout << "Incorrect input.\nPlease type a valid menu number:\n";
	}
	else {
		std::cout << "Please type a menu number:\n";

	}
}

inline void printChangePass()
{
	clearConsole();
	std::cout << "(Type b to go back.)\n\n";
	std::cout << "Change Password\n\n";
	std::cout << "\033[6H";
	std::cout << "New password: \n";
	std::cout << "\033[5H";
}

inline void successfulPassChange(char* input)
{
	clearConsole();
	std::cout << "Password successfully changed.\n\n";
	std::cout << "(Press enter to continue.)";
	std::cin.getline(input, 1);
}

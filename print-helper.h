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

void printHorizontalLine(const Level * lvl, const char thickness)
{
	std::cout << "++";
	for (unsigned short i = 0; i <= lvl->MAX_INSTR * 2; i++) {
		std::cout << thickness;
	}
	for (unsigned short i = 0; i <= lvl->SIZE * 2;i++) {
		if (i % 10 == 0) {
			std::cout << "++";
		}
		else if (i % 2 == 0) {
			std::cout << "+";
		}
		else {
			std::cout << thickness << thickness << thickness;
		}
	}
}

void printBoardTop(const Level* lvl)
{
	for (unsigned short line = 0; line < lvl->MAX_INSTR; line++) {
		unsigned short index = 0;
		std::cout << "||";

		for (unsigned short column = 0; column < lvl->MAX_INSTR; column++) {
			std::cout << "  ";
		}
		std::cout << " ";

		for (unsigned short column = 0; column <= lvl->SIZE * 2; column++) {
			if (column % 10 == 0) {
				std::cout << "||";
			}
			else if (column % 2 == 0) {
				std::cout << "|";
			}
			else {
				if (lvl->TOP_INSTR[line][index] == 0) {
					std::cout << "   ";
				}
				else {
					if (lvl->TOP_INSTR[line][index] < 10) {
						std::cout << " ";
					}
					std::cout << lvl->TOP_INSTR[line][index] << " ";
				}
				index++;
			}
		}
		std::cout << std::endl;
	}
}

void printBoardBody(const Level* lvl, unsigned short currProg[MAX_LVL_SIZE][MAX_LVL_SIZE])
{
	// also used for side coordinates
	unsigned short indexLine = 0;
	
	for (unsigned short line = 0; line <= lvl->SIZE * 2; line++) {
		if (line % 10 == 0) {
			printHorizontalLine(lvl, '=');
		}
		else if (line % 2 == 0) {
			printHorizontalLine(lvl, '-');
		}
		else
		{
			std::cout << "|| ";
			// print side elements
			unsigned short indexElement = 0;
			for (unsigned short column = 0; column < lvl->MAX_INSTR; column++) {
				if (lvl->SIDE_INSTR[indexLine][indexElement] == 0) {
					std::cout << "  ";
				}
				else {
					if (lvl->SIDE_INSTR[indexLine][indexElement] >= 10) {
						std::cout << '\b';
					}
					std::cout << lvl->SIDE_INSTR[indexLine][indexElement] << " ";
				}
				indexElement++;
			}
			// print main body
			indexElement = 0;
			for (unsigned short column = 0; column <= lvl->SIZE * 2; column++) {
				if (column % 10 == 0) {
					std::cout << "||";
				}
				else if (column % 2 == 0) {
					std::cout << "|";
				}
				else {
					if (currProg[indexLine][indexElement] == 0) {
						std::cout << " - ";
					}
					else if (currProg[indexLine][indexElement] == 1) {
						std::cout << " X ";
					}
					else {
						std::cout << "   ";
					}
					indexElement++;
				}
			}
			std::cout << " " << ++indexLine;
		}
		std::cout << std::endl;
	}
}

void printBottomCoord(const Level* lvl)
{
	for (unsigned short i = 0; i < lvl->MAX_INSTR * 2 + 5; i++) {
		std::cout << " ";
	}
	for (unsigned short i = 0; i < lvl->SIZE; i++) {
		if (i % 5 == 0 && i != 0) {
			std::cout << " ";
		}
		std::cout << " " << (char)('a' + i) << "  ";
	}
	std::cout << std::endl;
}

void printBoard(const Level* lvl, unsigned short currProg[MAX_LVL_SIZE][MAX_LVL_SIZE], unsigned short currLives)
{
	std::cout << "(Type b to go back (all progress will be saved).)\n\n";
	std::cout << "Level " << lvl->LEVEL << " - " << lvl->NAME << " (" << lvl->SIZE << "x" << lvl->SIZE << ")\n\n";
	std::cout << "Lives: " << currLives << "/" << lvl->MAX_LIVES << std::endl;
	
	printHorizontalLine(lvl, '=');
	std::cout << std::endl;
	printBoardTop(lvl);
	printBoardBody(lvl, currProg);
	printBottomCoord(lvl);

	std::cout << "\nGuesses:\t\t" << "Board state:\n";
	std::cout << "f - full\t\t" << "X - full\n";
	std::cout << "e - empty\t\t" << "- - empty\n\n";
}

void printLastLines(bool validAction, bool correctGuess, bool alrMarked, unsigned short currLives, Point print)
{
	std::cout << CSI << print.y << "H" << CSI << "J";

	if (!validAction) {
		std::cout << "Invalid input!\n";
	}
	else if (alrMarked) {
		std::cout << "Box is already marked!\n";
	}
	else if (!correctGuess) {
		std::cout << CSI << LIVES.y << ";" << LIVES.x << "H";
		std::cout << ERASE_CHAR << currLives;
		std::cout << CSI << print.y << "H";
		std::cout << "Wrong guess!\n" << "-1 Life\n";
	}
	std::cout << "Please type a coordinate and a guess (e.g.: a1 f):\n";
}

inline void gameOver(Point print, char* input)
{
	std::cout << CSI << "H" << CSI << "K"; //deletes first line
	std::cout << CSI << LIVES.y << ";" << LIVES.x << "H";
	std::cout << ERASE_CHAR << 0;

	std::cout << CSI << print.y << "H" << CSI << "J";
	std::cout << "Game Over!\n\n";

	std::cout << "(Press enter to continue.)\n";
	std::cin.getline(input, 1);
}

inline void successfulLevel(Point print, char* input, const Level * lvl)
{
	std::cout << CSI << "H" << CSI << "K"; //deletes first line
	std::cout << CSI << print.y << "H" << CSI << "J";
	std::cout << "Congratulations! Completed level ";
	std::cout << lvl->LEVEL << " - \"" << lvl->TITLE << "\"!\n\n";

	std::cout << "(Press enter to continue.)\n";
	std::cin.getline(input, 1);
}
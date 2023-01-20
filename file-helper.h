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
* <header with helper functions for files>
*
*/

#pragma once

void encrypt(char* str)
{
	size_t index = 0;
	while (str[index] != '\0') {
		str[index] ^= '!';
		str[index] ^= '@';
		str[index] ^= '%';
		index++;
	}
}

void decrypt(char* str)
{
	size_t index = 0;
	while (str[index] != '\0') {
		str[index] ^= '%';
		str[index] ^= '@';
		str[index] ^= '!';
		index++;
	}
}

void getSpecifiedLine(int line, std::fstream& account, char* string, const unsigned short strSize)
{
	account.seekg(0, std::ios::beg);
	for (size_t currentLine = 1; currentLine <= line; currentLine++) {
		account.getline(string, strSize);
	}
}

bool accountExists(const char* username, char* filePath)
{
	myStrCpy(filePath, username, MAX_INPUT_SIZE);
	myStrCatFront(filePath, ACCOUNT_DIRECTORY, MAX_INPUT_SIZE);
	myStrCatBack(filePath, FILE_EXTENSION, MAX_INPUT_SIZE);

	std::ifstream file(filePath);
	if (file.good()) {
		file.close();
		return true;
	}
	file.close();
	return false;
}

void defaultAccoutData(std::ofstream& account, char* input, int seed)
{
	encrypt(input);
	account << input << std::endl;

	srand(seed);

	for (unsigned short lvl = 0; lvl < NUM_OF_LVL; lvl++) {
		seed++;
		account << "0 " << (rand() % 2);
		if (lvl < NUM_OF_LVL - 2) {
			account << " " << lvl1_1.MAX_LIVES << std::endl;
		}
		else {
			account << " " << lvl5_1.MAX_LIVES << std::endl;
		}
	}

	// next unlocked level
	account << 1 << std::endl;
	// current level
	account << 0 << std::endl;
}

template <typename T>
bool openAccount(char* filePath, T& account)
{
	account.open(filePath);
	if (account.fail()) {
		account.close();
		std::cout << "Account data couldn't be accessed.\nPlease go back and try again.\n\n";
		std::cout << "(Press enter to continue.)";
		do {
			std::cin.getline(filePath, MAX_INPUT_SIZE);
		} while (filePath[0] != '\0');
		return false;
	}
	return true;
}

void readCurrProg(unsigned short(&currProg)[MAX_LVL_SIZE][MAX_LVL_SIZE], std::fstream& account)
{
	account.seekg(-3, std::ios::end);
	for (int line = MAX_LVL_SIZE - 1; line >= 0; line--) {
		for (int element = MAX_LVL_SIZE - 1; element >= 0; element--) {
			char c;
			account.get(c);
			currProg[line][element] = (unsigned short)(c - '0');
			account.seekg(-3, std::ios::cur);
		}
		account.seekg(-1, std::ios::cur);
	}
}

void copyAccData(std::fstream& account, char (&data)[MAX_FILE_LINES][MAX_LINE_LEN])
{
	account.seekg(0, std::ios::beg);
	for (unsigned short line = 0; line < MAX_FILE_LINES; line++) {
		account.getline(data[line], MAX_LINE_LEN);
	}
}

bool rewriteFileData(char* filePath, char newData[MAX_FILE_LINES][MAX_LINE_LEN], std::fstream& account)
{
	account.close();

	std::ofstream file;
	if (!openAccount(filePath, file)) {
		return false;
	}

	file.seekp(0, std::ios::beg);

	for (unsigned short line = 0; line < MAX_FILE_LINES; line++) {
		if (newData[line][0] != '\0') {
			file << newData[line] << std::endl;
		}
	}

	file.close();

	if (!openAccount(filePath, account)) {
		return false;
	}
	return true;
}

void finishedLvlProg(char (&newData)[MAX_FILE_LINES][MAX_LINE_LEN],
	unsigned short currLives, const Level * lvl)
{
	newData[lvl->LEVEL + FILE_LINE::pass - 1][0] = '1';
	newData[lvl->LEVEL + FILE_LINE::pass - 1][4] = (char)(currLives + '0');
	if ((char)(lvl->LEVEL + 1 + '0') > newData[FILE_LINE::nextUnlocked - 1][0]) {
		newData[FILE_LINE::nextUnlocked - 1][0] = (char)(lvl->LEVEL + 1 + '0');
	}
	newData[FILE_LINE::curLvl - 1][0] = '0';
}

void unfinishedLvlProg(char (&newData)[MAX_FILE_LINES][MAX_LINE_LEN],
	unsigned short currProg[MAX_LVL_SIZE][MAX_LVL_SIZE], unsigned short currLives, const Level* lvl)
{
	newData[FILE_LINE::curLvl - 1][0] = (char)(lvl->LEVEL + '0');
	newData[FILE_LINE::curLvl - 1][1] = ' ';
	newData[FILE_LINE::curLvl - 1][2] = (char)(lvl->VERSION + '0');
	newData[FILE_LINE::curLvl - 1][3] = ' ';
	newData[FILE_LINE::curLvl - 1][4] = (char)(currLives + '0');

	for (unsigned short line = 0; line < MAX_LVL_SIZE; line++) {
		for (unsigned short element = 0; element < MAX_LINE_LEN; element++) {
			if (element % 2 == 0) {
				newData[line + matrixStart - 1][element] = (char)(currProg[line][element / 2] + '0');
			}
			else {
				newData[line + matrixStart - 1][element] = ' ';
			}
		}
		newData[line + matrixStart - 1][MAX_LINE_LEN - 1] = '\0';
	}
}

void getLvlStatus(char* input, std::fstream& account, char (&lvlStatus)[NUM_OF_LVL][26])
{
	getSpecifiedLine(nextUnlocked, account, input, MAX_INPUT_SIZE);
	unsigned short readLevel = input[0] - '0';

	for (unsigned short level = 0; level < NUM_OF_LVL; level++) {
		getSpecifiedLine(FILE_LINE::lvl1 + level, account, input, MAX_INPUT_SIZE);
		if (level + 1 > readLevel) {
			myStrCpy(lvlStatus[level],"(Locked)", 26);
		}
		else if (input[0] == '1') {
			char temp[26] = "(Completed with   lives)";
			temp[16] = input[4];
			myStrCpy(lvlStatus[level], temp, 26);
		}
		else {
			myStrCpy(lvlStatus[level], "(Next level)", 26);
		}
	}

	getSpecifiedLine(curLvl, account, input, MAX_INPUT_SIZE);
	if (input[0] == '0') {
		return;
	}
	readLevel = input[0] - '0';
	myStrCpy(lvlStatus[readLevel - 1], "(In progress)", 26);
}
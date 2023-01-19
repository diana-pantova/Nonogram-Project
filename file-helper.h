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

void defaultAccoutData(std::ofstream& account, char* input)
{
	encrypt(input);
	account << input << std::endl;
	for (unsigned short lineCount = lvl1; lineCount <= curLvl; lineCount++) {
		account << "0" << std::endl;
	}
}

bool openAccount(char* filePath, std::fstream& account)
{
	account.open(filePath);

	if (account.fail()) {
		account.close();
		std::cout << "Account data couldn't be accessed.\nPlease go back and try again.\n\n";
		std::cout << "(Press enter to continue.)";
		std::cin.getline(filePath, 1);
		return false;
	}

	return true;
}

void rewriteFileData(char* filePath, char newData[MAX_FILE_LINES][MAX_LINE_LEN], std::fstream& account)
{
	account.close();

	std::ofstream file;
	file.open(filePath);
	file.seekp(0, std::ios::beg);

	for (unsigned short line = 0; line < MAX_FILE_LINES; line++) {
		file << newData[line] << std::endl;
	}

	file.close();
	account.open(filePath);
}


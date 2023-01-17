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
* <file with miscellaneous utility functions>
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

/**
* @return -1 if 'b' - command to go back;
*  0 if the string can be a valid username;
*  1 if it's too short;
*  2 if it's too long;
*  3 if it contains forbidden characters
*/
int checkUsernameChars(char* name)
{
	size_t length = myStrLen(name);

	if (length == 1 && name[0] == 'b') {
		return -1;
	}

	if (length < MIN_USERNAME_LEN) {
		return 1;
	}
	else if (length > MAX_USERNAME_LEN ) {
		return 2;
	}

	// checks if the username contains only valid characters
	for (size_t index = 0; name[index] != '\0'; index++) {
		if (name[index] < '0' && name[index] != '-' || name[index] > 'z') {
			return 3;
		} 
		else if (name[index] > '9' && name[index] < 'A') {
			return 3;
		}
		else if (name[index] > 'Z' && name[index] < 'a' && name[index] != '_') {
			return 3;
		}
	}

	return 0;
}

bool accountExists(const char* username, char* fileName)
{
	myStrCpy(fileName, username, MAX_INPUT_SIZE);
	myStrCatFront(fileName, ACCOUNT_DIRECTORY, MAX_INPUT_SIZE);
	myStrCatBack(fileName, FILE_EXTENSION, MAX_INPUT_SIZE);
	
	std::ifstream file(fileName);
	if (file.good()) {
		file.close();
		return true;
	}
	file.close();
	return false;
}

/**
* @return false if the user chose to go back,
* true if the user finished the account creation process
*/
bool createValidUsername(char* input, char* fileName)
{
	std::cout << "Enter a username:\n";
	int usernameChars = 1;
	bool takenUsername = true;
	
	do {
		std::cin.getline(input, MAX_INPUT_SIZE);

		usernameChars = checkUsernameChars(input);

		switch (usernameChars) {
		case 1:
			std::cout << "Username must contain at least " << MIN_USERNAME_LEN << " characters. Please try again.\n";
			continue;
		case 2:
			std::cout << "Username must be no longer than " << MAX_USERNAME_LEN << " characters. Please try again.\n";
			continue;
		case 3:
			std::cout << "Usernames must contain only uppercase and lowercase latin letters,\n"
				<< "numbers, underscores and dashes. Please try again.\n";
			continue;
		case 0:
			// username is valid
			break;
		case -1: // go back, ending the account creation process
			return false;
		default:
			std::cout << "Error. Please try again.\n";
			continue;
		}

		takenUsername = accountExists(input, fileName);
		if (takenUsername) {
			std::cout << "Username is already taken. Please try again.\n";
		}

	} while (usernameChars != 0 || takenUsername);
	
	return true;
}

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

bool isValidPass(char* pass)
{
	size_t length = myStrLen(pass);

	if (length < MIN_PASSWORD_LEN) {
		std::cout << "Password must be at least " << MIN_PASSWORD_LEN << " characters long. Please try again.\n";
		return false;
	}
	else if (length > MAX_PASSWORD_LEN) {
		std::cout << "Password must be no longer than " << MAX_PASSWORD_LEN << " characters. Please try again.\n";
		return false;
	}

	for (size_t index = 0; pass[index] != '\0'; index++) {
		if (pass[index] < '!' || pass[index] > '~') {
			std::cout << "Passowrd contains forbidden characters. Please try again.\n";
			return false;
		}
	}

	return true;
}

void createValidPass(char* input)
{
	std::cout << "Enter a password:\n";
	bool isValid;

	do {
		std::cin.getline(input, MAX_INPUT_SIZE);
		isValid = isValidPass(input);
		if (isValid) {
			break;
		}
		
	} while (!isValid);
}

inline void successfulSignup(char* input)
{
	clearConsole();
	std::cout << "Account successfully created!\n";
	std::cout << "You can now log in from the Login Menu.\n";
	std::cout << "Enjoy!\n\n";

	std::cout << "(Press Enter to go back.)\n";
	std::cin.getline(input, 1);
}
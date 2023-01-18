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

inline void printLoginMenu()
{
	std::cout << "(Type 'b' to go back.)\n\n";
	std::cout << "Login\n" << "Log into an existing account.\n\n";
	std::cout << "\033[E" << "Password: " << "\033[F"; // moves cursor forward, prints, then back again
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

/**
* @return false if the user chose to go back,
* true if the user finished the account creation process
*/
bool createValidUsername(char* input, char* filePath)
{
	int usernameChars = 1;
	bool takenUsername = true;
	
	do {
		std::cout << "Username: ";
		std::cin.getline(input, MAX_INPUT_SIZE);

		usernameChars = checkUsernameChars(input);

		switch (usernameChars) {
		case 1:
			std::cout << "\n\n\033[J" << "Username must contain at least " << MIN_USERNAME_LEN;
			std::cout << " characters.\nPlease try again.";
			std::cout << "\033[4F\033[K"; // moves the cursor to username line and erases
			continue;
		case 2:
			std::cout << "\n\n\033[J" << "Username must be no longer than " << MAX_USERNAME_LEN;
			std::cout << " characters.\nPlease try again.";
			std::cout << "\033[4F\033[K";
			continue;
		case 3:
			std::cout << "\n\n\033[J" << "Usernames must contain only uppercase and lowercase latin letters,\n"
				<< "numbers, underscores and dashes.\nPlease try again.";
			std::cout << "\033[5F\033[K";
			continue;
		case 0:
			// username is valid
			break;
		case -1: // go back, ending the account creation process
			return false;
		default:
			std::cout << "\n\nError. Please try again.";
			std::cout << "\033[2F\033[K";
			continue;
		}

		takenUsername = accountExists(input, filePath);
		if (takenUsername) {
			std::cout << "\n\n\033[J" << "Username is already taken. Please try again.";
			std::cout << "\033[3F\033[K"; // moves the cursor to username line and erases
		}

	} while (usernameChars != 0 || takenUsername);
	
	std::cout << "\033[J"; // erases unnecessary lines
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
		std::cout << "\n\033[J" << "Password must be at least " << MIN_PASSWORD_LEN;
		std::cout << " characters long.\nPlease try again.";
		std::cout << "\033[3F\033[K"; // moves the cursor to password line and erases
		return false;
	}
	else if (length > MAX_PASSWORD_LEN) {
		std::cout << "\n\033[J" << "Password must be no longer than " << MAX_PASSWORD_LEN;
		std::cout << " characters.\nPlease try again.";
		std::cout << "\033[3F\033[K";
		return false;
	}

	for (size_t index = 0; pass[index] != '\0'; index++) {
		if (pass[index] < '!' || pass[index] > '~') {
			std::cout << "\n\033[J" << "Passowrd contains forbidden characters. Please try again.";
			std::cout << "\033[2F\033[K";
			return false;
		}
	}

	return true;
}

void createValidPass(char* input)
{
	bool isValid = false;
	do {
		std::cout << "Password: ";
		std::cin.getline(input, MAX_INPUT_SIZE);
		isValid = isValidPass(input);
		if (isValid) {
			break;
		}
	} while (!isValid);
}

void getSpecifiedLine(int line, std::ifstream &account, char* string)
{
	for (size_t currentLine = 1; currentLine <= line; currentLine++) {
		account >> string;
	}
}

bool correctPassowrd(char* input, char* filePath)
{
	std::ifstream account;
	account.open(filePath);
	
	if (account.fail()) {
		std::cout <<  "\n\033[J" << "Account data couldn't be accessed.\nPlease go back and try again.";
		return false;
	}

	char pass[MAX_INPUT_SIZE] = {};
	
	getSpecifiedLine(FILE_LINE::pass, account, pass);

	decrypt(pass);
	int match = myStrCmp(input, pass);
	account.close();

	return match == 0;
}

bool loginUsername(char* input, char* filePath)
{
	bool validUsername = false;
	do {
		std::cout << "Username: ";
		std::cin.getline(input, MAX_INPUT_SIZE);
		
		if (myStrLen(input) == 1 && input[0] == 'b') {
			return false;
		}

		validUsername = accountExists(input, filePath);
		if (!validUsername) {
			std::cout << "\n\nAn account with this username doesn't exist.\n";
			std::cout << "If you don't have an account yet,\ngo back and choose Sign-up.\n";
			std::cout << "\033[6F\033[K"; // moves cursor back and erases line
		}

	} while (!validUsername);

	std::cout << "\033[J"; // erases unnecessary lines
	return true;
}

bool loginPassword(char* input, char* filePath)
{
	bool validPass = false;
	do {
		std::cout << "Password: ";
		std::cin.getline(input, MAX_INPUT_SIZE);
		
		if (myStrLen(input) == 1 && input[0] == 'b') {
			return false;
		
		}
		validPass = correctPassowrd(input, filePath);
		if (!validPass) {
			std::cout << "\nIncorrect password. Please try again.";
			std::cout << "\033[2F\033[K"; // moves cursor back and erases line
		}

	} while (!validPass);
	return true;
}

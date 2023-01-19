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
* <header with miscellaneous utility functions>
*
*/

#pragma once

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
		// TODO: transfer to different function
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

void createValidPass(char* input, const char* message)
{
	bool isValid = false;
	do {
		std::cout << message;
		std::cin.getline(input, MAX_INPUT_SIZE);
		isValid = isValidPass(input);
		if (isValid) {
			break;
		}
	} while (!isValid);
}

bool correctPassowrd(char* input, char* filePath)
{
	std::fstream account;
	account.open(filePath);
	
	if (account.fail()) {
		std::cout <<  "\n\033[J" << "Account data couldn't be accessed.\nPlease go back and try again.";
		return false;
	}

	char pass[MAX_PASSWORD_LEN] = {};
	
	getSpecifiedLine(FILE_LINE::pass, account, pass, MAX_PASSWORD_LEN + 1);

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
		
		if (input[0] == 'b' && input[1] == '\0') {
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
		
		if (input[0] == 'b' && input[1] == '\0') {
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

bool confirmPass(char* input, char* correctPass)
{
	do {
		std::cout << "Current password: ";
		std::cin.getline(input, MAX_INPUT_SIZE);

		if (input[0] == 'b' && input[1] == '\0') {
			return false;
		}
		if (myStrCmp(input, correctPass) == 0) {
			break;
		}
		else {
			std::cout << "\n\nIncorrect password. Please try again.";
			std::cout << "\033[5H\033[K";
		}

	} while (true);
	
	return true;
}

void changePassword(char* input, std::fstream& account, char* filePath)
{
	printChangePass();

	char correctPass[MAX_PASSWORD_LEN + 1] = {};
	//getSpecifiedLine(FILE_LINE::pass, account, correctPass);
	getSpecifiedLine(pass, account, correctPass,MAX_PASSWORD_LEN + 1);
	decrypt(correctPass);

	if (!confirmPass(input, correctPass)) {
		return;
	}

	std::cout << "\033[H\033[K";
	std::cout << "(Cannot go back until password has been successfully changed.)";
	std::cout << "\033[6H\033[J";

	createValidPass(input, "New password: ");
	encrypt(input);

	char newData[MAX_FILE_LINES][MAX_LINE_LEN] = {};
	myStrCpy(newData[pass - 1], input, MAX_FILE_LINES);


	account.seekp(0, std::ios::beg);
	for (unsigned short line = 0; line < MAX_FILE_LINES; line++) {
		if (line != pass - 1) {
			account.getline(newData[line], MAX_LINE_LEN);
		}
	}
	
	rewriteFileData(filePath, newData, account);

	successfulPassChange(input);
}

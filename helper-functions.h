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
			std::cout << "\n\n" << CSI << "J" << "Username must contain at least " << MIN_USERNAME_LEN;
			std::cout << " characters.\nPlease try again.";
			std::cout << CSI << "4F" << CSI << "K"; // moves the cursor to username line and erases
			continue;
		case 2:
			std::cout << "\n\n" << CSI << "J" << "Username must be no longer than " << MAX_USERNAME_LEN;
			std::cout << " characters.\nPlease try again.";
			std::cout << CSI << "4F" << CSI << "K";;
			continue;
		case 3:
			std::cout << "\n\n" << CSI << "J" << "Usernames must contain only uppercase and lowercase latin letters,\n"
				<< "numbers, underscores and dashes.\nPlease try again.";
			std::cout << CSI << "5F" << CSI << "K";
			continue;
		case 0:
			// username is valid
			break;
		case -1: // go back, ending the account creation process
			return false;
		default:
			std::cout << "\n\nError. Please try again.";
			std::cout << CSI << "2F" << CSI << "K";
			continue;
		}

		takenUsername = accountExists(input, filePath);
		if (takenUsername) {
			std::cout << "\n\n" << CSI << "J" << "Username is already taken. Please try again.";
			std::cout << CSI << "3F" << CSI << "K"; // moves the cursor to username line and erases
		}

	} while (usernameChars != 0 || takenUsername);
	
	std::cout << CSI << "J"; // erases unnecessary lines
	return true;
}

bool isValidPass(char* pass)
{
	size_t length = myStrLen(pass);

	if (length < MIN_PASSWORD_LEN) {
		std::cout << "\n" << CSI << "J" << "Password must be at least " << MIN_PASSWORD_LEN;
		std::cout << " characters long.\nPlease try again.";
		std::cout << CSI << "3F" << CSI << "K"; // moves the cursor to password line and erases
		return false;
	}
	else if (length > MAX_PASSWORD_LEN) {
		std::cout << "\n" << CSI << "J" << "Password must be no longer than " << MAX_PASSWORD_LEN;
		std::cout << " characters.\nPlease try again.";
		std::cout << CSI << "3F" << CSI << "K";
		return false;
	}

	for (size_t index = 0; pass[index] != '\0'; index++) {
		if (pass[index] < '!' || pass[index] > '~') {
			std::cout << "\n" << CSI << "J" << "Passowrd contains forbidden characters. Please try again.";
			std::cout << CSI << "2F" << CSI << "K";
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

int createSeed(char* username)
{
	int seed = 0;
	unsigned short index = 0;
	while (username[index] != '\0') {
		seed += username[index];
		index++;
	}
	return seed;
}

bool correctPassowrd(char* input, char* filePath)
{
	std::fstream account;
	
	if (!openAccount(filePath, account)) {
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
			std::cout << CSI << "6F" << CSI << "K"; // moves cursor back and erases line
		}

	} while (!validUsername);

	std::cout << CSI << "J"; // erases unnecessary lines
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
			std::cout << CSI << "2F" << CSI << "K"; // moves cursor back and erases line
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
			std::cout << CSI << "5H" << CSI << "K";
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

	std::cout << CSI << "H" << CSI << "K";
	std::cout << "(Cannot go back until password has been successfully changed.)";
	std::cout << CSI << "6H" << CSI << "J";

	createValidPass(input, "New password: ");
	encrypt(input);

	char newData[MAX_FILE_LINES][MAX_LINE_LEN] = {};
	myStrCpy(newData[pass - 1], input, MAX_FILE_LINES);


	account.seekg(0, std::ios::beg);
	for (unsigned short line = 0; line < MAX_FILE_LINES; line++) {
		if (line != pass - 1) {
			account.getline(newData[line], MAX_LINE_LEN);
		}
	}
	newData[pass][0] = '\0';
	
	rewriteFileData(filePath, newData, account);

	successfulPassChange(input);
}

const Level* listOfLevels(unsigned short level, bool version)
{
	switch (version) {
	case 0:
		switch (level) {
		case 1:
			return &lvl1_1;
		case 2: 
			return &lvl2_1;
		case 3: 
			return &lvl3_1;
		case 4:
			return &lvl4_1;
		case 5:
			return &lvl5_1;
		default:
			return nullptr;
		}
	case 1:
		switch (level) {
		case 1:
			return &lvl1_2;
		case 2:
			return &lvl2_2;
		case 3:
			return &lvl3_2;
		case 4:
			return &lvl4_2;
		case 5:
			return &lvl5_2;
		default:
			return nullptr;
		}
	}
	return nullptr;
}

void defineCurrProg(unsigned short (&currProg)[MAX_LVL_SIZE][MAX_LVL_SIZE])
{
	for (int i = 0; i < MAX_LVL_SIZE; i++) {
		for (int j = 0; j < MAX_LVL_SIZE; j++) {
			currProg[i][j] = 2;
		}
	}
}

const Level * pickCorrectLevel(char* input, std::fstream& account, unsigned short& currLives, unsigned short (&currProg)[MAX_LVL_SIZE][MAX_LVL_SIZE])
{
	unsigned short level;
	bool version;

	getSpecifiedLine(FILE_LINE::curLvl, account, input, MAX_INPUT_SIZE);
	
	// if no game is in progress
	if (input[0] == '0') {
		getSpecifiedLine(FILE_LINE::nextUnlocked, account, input, MAX_INPUT_SIZE);
		level = input[0] - '0';
		getSpecifiedLine(level + FILE_LINE::pass, account, input, MAX_INPUT_SIZE);
		version = input[2] - '0';
		currLives = input[4] - '0';
		defineCurrProg(currProg);
	}
	else {
		level = input[0] - '0';
		version = input[2] - '0';
		currLives = input[4] - '0';
		readCurrProg(currProg, account);
	}

	const Level* correctLevel = listOfLevels(level, version);

	return correctLevel;
}

const Level* pickedLvlData(const Level* lvl, unsigned short &currLives, unsigned short (&currProg)[MAX_LVL_SIZE][MAX_LVL_SIZE])
{
	currLives = lvl->MAX_LIVES;
	defineCurrProg(currProg);
	return lvl;
}

void assignPointCoord(const Level * lvl, Point& A1, Point& print)
{
	A1 = {
		(unsigned short)(COORD_HELPER.x + 2 * lvl->MAX_INSTR),
		(unsigned short)(COORD_HELPER.y + lvl->MAX_INSTR)
	};
	print = {
		1,
		(unsigned short)(2 * lvl->SIZE + A1.y + 6)
	};
}

bool validGameAction(char* input, const Level * lvl, bool bigBoard)
{
	size_t inputLen = myStrLen(input);

	if (inputLen == 4) {
		if (input[0] < 'a' || input[0] >= ('a' + lvl->SIZE)) {
			return false;
		}
		else if (input[1] < '1' || input[1] >= ('1' + lvl->SIZE)) {
			return false;
		}
		else if (input[2] != ' ') {
			return false;
		}
		else if (!(input[3] == 'f' || input[3] == 'e')) {
			return false;
		}
		return true;
	}
	else if (inputLen == 5) {
		if (input[0] < 'a' || input[0] >= ('a' + lvl->SIZE)) {
			return false;
		}
		else if (input[1] < '1' || input[1] > '9') {
			return false;
		}
		else if (input[2] < '0' || input[2] > ('0' + lvl->SIZE % 10)) {
			return false;
		}
		else if (input[3] != ' ') {
			return false;
		}
		else if (!(input[4] == 'f' || input[4] == 'e')) {
			return false;
		}
		return true;
	}

	return false;
}

void getActionCoord(Point& action, char* input, bool bigBoard)
{
	action.x = input[0] - 'a';

	if (bigBoard && input[2] != ' ') {
		action.y = (input[1] - '1' + 1) * 10;
		action.y += input[2] - '1';
	}
	else {
		action.y = input[1] - '1';
	}
}

bool getGuess(char* input, bool bigBoard)
{
	if (bigBoard && input[3] == ' ') {
		return input[4] == 'f';
	}
	return input[3] == 'f';
}

inline bool isCorrectGuess(Point action, bool guess, const Level* lvl)
{
	if (lvl->DESCRIPTION[action.y][action.x] == guess) {
		return true;
	}
	return false;
}

/**
* @return - true if the row is correctly and fully filled
*/
bool checkRows(Point action, unsigned short currProg[MAX_LVL_SIZE][MAX_LVL_SIZE], const Level* lvl)
{
	for (unsigned short element = 0; element < lvl->SIZE; element++) {
		if (lvl->DESCRIPTION[action.y][element] == 1) {
			if (currProg[action.y][element] != 1) {
				return false;
			}
		}
	}
	return true;
}

/**
* @return - true if the column is correctly and fully filled
*/
bool checkColumns(Point action, unsigned short currProg[MAX_LVL_SIZE][MAX_LVL_SIZE], const Level* lvl)
{
	for (unsigned short line = 0; line < lvl->SIZE; line++) {
		if (lvl->DESCRIPTION[line][action.x] == 1) {
			if (currProg[line][action.x] != 1) {
				return false;
			}
		}
	}
	return true;
}

bool checkFullBoard(unsigned short currProg[MAX_LVL_SIZE][MAX_LVL_SIZE], const Level * lvl)
{
	for (unsigned short line = 0; line < lvl->SIZE; line++) {
		for (unsigned short element = 0; element < lvl->SIZE; element++) {
			if (currProg[line][element] != (unsigned short)lvl->DESCRIPTION[line][element]) {
				return false;
			}
		}
	}
	return true;
}

void updateBox(Point console, bool guess)
{
	std::cout << CSI << console.y << ";" << console.x << "H";
	if (guess) {
		std::cout << "X";
		return;
	}
	std::cout << "-";
}

void updateRow(unsigned short row, const Level* lvl, 
	unsigned short currProg[MAX_LVL_SIZE][MAX_LVL_SIZE], Point A1, unsigned short console_y)
{
	for (unsigned short element = 0; element < lvl->SIZE; element++)
	{
		if (lvl->DESCRIPTION[row][element] == 0) {
			currProg[row][element] = 0;
			std::cout << CSI << console_y << ";" << (A1.x + element * OFFSET.x + element / 5) << "H";
			std::cout << "-";
		}
	}
}

void updateColumn(unsigned short column, const Level* lvl,
	unsigned short currProg[MAX_LVL_SIZE][MAX_LVL_SIZE], Point A1, unsigned short console_x)
{
	for (unsigned short line = 0; line < lvl->SIZE; line++)
	{
		if (lvl->DESCRIPTION[line][column] == 0) {
			currProg[line][column] = 0;
			std::cout << CSI << (A1.y + line * OFFSET.y) << ";" << console_x << "H";
			std::cout << "-";
		}
	}
}

bool updateBoard(Point action, unsigned short currProg[MAX_LVL_SIZE][MAX_LVL_SIZE], const Level* lvl, Point A1)
{
	Point console = {
	(unsigned short)(A1.x + action.x * OFFSET.x + action.x / 5),
	(unsigned short)(A1.y + action.y * OFFSET.y)
	};

	updateBox(console, currProg[action.y][action.x]);

	bool fullRow = checkRows(action, currProg, lvl);
	bool fullColumn = checkColumns(action, currProg, lvl);

	if (fullRow) {
		updateRow(action.y, lvl, currProg, A1, console.y);
	}
	
	if (fullColumn) {
		updateColumn(action.x, lvl, currProg, A1, console.x);
	}
	
	return checkFullBoard(currProg, lvl);
}

unsigned short assignResult(bool goBack, bool alive, bool success)
{
	if (success) {
		return 0;
	}
	if (!alive) {
		return 1;
	}
	if (goBack) {
		return 2;
	}
	return 2;
}

bool results(unsigned short result, Point print, char* input, unsigned short currLives,
	unsigned short currProg[MAX_LVL_SIZE][MAX_LVL_SIZE], const Level * lvl, char* filePath, std::fstream& account)
{
	char newData[MAX_FILE_LINES][MAX_LINE_LEN] = {};
	copyAccData(account, newData);

	switch (result) {
	case 0:
		finishedLvlProg(newData, currLives, lvl);
		successfulLevel(print, input, lvl);
		break;
	case 1:
		newData[FILE_LINE::curLvl][0] = '0';
		gameOver(print, input);
		break;
	case 2:
		unfinishedLvlProg(newData, currProg, currLives, lvl);
		break;
	default:
		break;
	}
	if (!rewriteFileData(filePath, newData, account)) {
		false;
	}

	return true;
}


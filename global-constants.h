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
* <header with global constants>
*
*/

#pragma once

const size_t MAX_INPUT_SIZE = 101;

const size_t MIN_USERNAME_LEN = 3;
const size_t MAX_USERNAME_LEN = 20;

const size_t MIN_PASSWORD_LEN = 5;
const size_t MAX_PASSWORD_LEN = 20;

const unsigned short NUM_OF_LVL = 5;
const unsigned short MAX_LVL_SIZE = 15;
const unsigned short MAX_INSTR_SIZE = 5;

const unsigned short MAX_FILE_LINES = 2 + NUM_OF_LVL + 2 + MAX_LVL_SIZE + 1;
const unsigned short MAX_LINE_LEN = MAX_LVL_SIZE * 2;

struct Point {
	unsigned short x;
	unsigned short y;
};

const Point COORD_HELPER = { 7, 8 };
const Point OFFSET = { 4, 2 };
const Point LIVES = { 8, 5 };

const char* ERASE_CHAR = "\b ";
const char* CSI = "\033[";

const char ACCOUNT_DIRECTORY[] = "./UserAccounts/";
const char FILE_EXTENSION[] = ".txt";

const enum MENU_SELECTION
{
	quit = 0,
	stMenu = 1,
	login = 2,
	signup = 3,
	account = 4
};

const enum FILE_LINE
{
	name = 1,
	pass = 2,
	lvl1 = 3,
	lvl2 = 4,
	lvl3 = 5,
	lvl4 = 6,
	lvl5 = 7,
	nextUnlocked = 8,
	curLvl = 9,
	matrixStart = 10
};
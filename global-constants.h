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
* <file with global constants>
*
*/

#pragma once

const size_t MAX_INPUT_SIZE = 101;

const size_t MIN_USERNAME_LEN = 3;
const size_t MAX_USERNAME_LEN = 20;

const size_t MIN_PASSWORD_LEN = 5;
const size_t MAX_PASSWORD_LEN = 20;

const char ACCOUNT_DIRECTORY[] = "./UserAccounts/";
const char FILE_EXTENSION[] = ".txt";

const enum MENU_SELECTION
{
	quit = 0,
	stMenu = 1,
	login = 2,
	signup = 3,
	account = 4,
	game = 5,
	lvlProg = 6,
	settings = 7,
	changeName = 8,
	changePass = 9
};
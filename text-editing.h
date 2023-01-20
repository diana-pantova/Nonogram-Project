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
* <header with helper functions for text editing>
*
*/

#pragma once

void clearConsole() {
	std::cout << CSI << "H" << CSI << "J";
}

/**
* @return - the length of the char array (excluding '\0')
*/
size_t myStrLen(const char* str)
{
	if (str == nullptr) {
		std::cout << __FILE__ << ": " << __func__ << ": " << __LINE__ << ": ";
		std::cout << "Error! Null pointer!" << std::endl;
		return 0;
	}
	size_t length = 0;
	while (str[length++] != '\0');
	return --length;
}

/**
* @param destination - array to copy to
* @param source - array to copy from
* @param destSize - max capacity of destination array
* @return - copies the contents of the source array to the destination array
*/
void myStrCpy(char* destination, const char* source, size_t destSize)
{
	if (source == nullptr || destination == nullptr) {
		std::cout << __FILE__ << ": " << __func__ << ": " << __LINE__ << ": ";
		std::cout << "Error! Null pointer!" << std::endl;
		return;
	}

	size_t srcLen = myStrLen(source);

	if (destSize < srcLen + 1) {
		std::cout << __FILE__ << ": " << __func__ << ": " << __LINE__ << ": ";
		std::cout << "Error! Source is larger than destination!" << std::endl;
		return;
	}

	size_t index = 0;
	while (source[index] != '\0') {
		destination[index] = source[index];
		index++;
	}
	destination[index] = '\0';
}

/**
* @param string - array to be edited
* @param positions - number of positions with which the to push the string right
* @param strSize - max capacity of the array
* @return - Moves the content of the array to the right with a specified amount of positions.
* Doesn't change the beggining of the array.
*/
void myStrShiftRight(char* string, size_t positions, size_t strSize)
{
	if (string == nullptr) {
		std::cout << __FILE__ << ": " << __func__ << ": " << __LINE__ << ": ";
		std::cout << "Error! Null pointer!" << std::endl;
		return;
	}
	size_t strLen = myStrLen(string);

	if (strLen + positions + 1 > strSize) {
		std::cout << __FILE__ << ": " << __func__ << ": " << __LINE__ << ": ";
		std::cout << "Error! Destination array is too small!" << std::endl;
		return;
	}

	for (int index = (int)strLen; index >= 0; index--) {
		string[index + positions] = string[index];
	}
}

/**
* @param destination - array to be edited
* @param source - array to be added
* @param destSize - max size of destination array
* @return - adds source array to the back of destination array
*/
void myStrCatBack(char* destination, const char* source, size_t destSize)
{
	if (destination == nullptr || source == nullptr) {
		std::cout << __FILE__ << ": " << __func__ << ": " << __LINE__ << ": ";
		std::cout << "Error! Null pointer!" << std::endl;
		return;
	}

	size_t destLen = myStrLen(destination);
	size_t srcLen = myStrLen(source);

	// +1 for '\0'
	if (destLen + srcLen + 1 > destSize) {
		std::cout << __FILE__ << ": " << __func__ << ": " << __LINE__ << ": ";
		std::cout << "Error! Destination array is too small!" << std::endl;
		return;
	}

	size_t i = 0;
	while (i < srcLen) {
		destination[destLen + i] = source[i];
		i++;
	}
	destination[destLen + i] = '\0';
}

/**
* @param destination - array to be edited
* @param source - array to be added
* @param destSize - max size of destination array
* @return - adds source array to the front of destination array
*/
void myStrCatFront(char* destination, const char* source, size_t destSize)
{
	if (destination == nullptr || source == nullptr) {
		std::cout << __FILE__ << ": " << __func__ << ": " << __LINE__ << ": ";
		std::cout << "Error! Null pointer!" << std::endl;
		return;
	}

	size_t destLen = myStrLen(destination);
	size_t srcLen = myStrLen(source);

	// +1 for '\0'
	if (destLen + srcLen + 1 > destSize) {
		std::cout << __FILE__ << ": " << __func__ << ": " << __LINE__ << ": ";
		std::cout << "Error! Destination array is too small!" << std::endl;
		return;
	}

	myStrShiftRight(destination, srcLen, destSize);

	size_t i = 0;
	while (i < srcLen) {
		destination[i] = source[i];
		i++;
	}
}

/**
* @return - 0 if the strings match
*/
int myStrCmp(const char* str1, const char* str2)
{
	size_t index = 0;
	while (str1[index] != '\0' && str1[index] == str2[index])
	{
		++index;
	}
	return str1[index] - str2[index];
}
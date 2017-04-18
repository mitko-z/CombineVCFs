#pragma once
#include "BaseMenu.h"
#include <string> // + operator overload
#include <iostream> // user input
#include <sstream> // user formated input management

class RangeMenu : public BaseMenu
{
private:
	unsigned int m_iLowerRange;
	unsigned int m_iUpperRange;
public:
	// to do: make the constructor to get automatically the range from the current folder
	RangeMenu() :m_iLowerRange(1), m_iUpperRange(1) {}

	std::string getRange();

	void processMenu();

	unsigned int getLower() { return m_iLowerRange; }
	unsigned int getUpper() { return m_iUpperRange; }
};
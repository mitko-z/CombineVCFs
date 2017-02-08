#pragma once
#include <string>	// std::string management
#include <iostream> // std::cin

class BaseMenu
{
public:
	BaseMenu() :m_sMenuText("") {}
	BaseMenu(std::string menuText) :m_sMenuText(menuText) {}

	// prints the menuText field on the screen
	void printText();

	virtual void processMenu() {} 

protected:
	std::string m_sMenuText;
	
	const std::string NEW_LINE = "\n";
	const unsigned int ROWS_TO_CLEAR = 40;

	// some helpful methods for menus
	void clearScreen();

	void pressAnyKey();

	int getChoice();
};
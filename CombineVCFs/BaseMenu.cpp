#include "BaseMenu.h"
#include <iostream> // std::cout

void BaseMenu::printText()
{
	clearScreen();
	std::cout << m_sMenuText << std::endl;
}

void BaseMenu::clearScreen()
{
	for (int i = 0; i < ROWS_TO_CLEAR; i++)
	{
		std::cout << std::endl;
	}
}

void BaseMenu::pressAnyKey()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
	system("pause");
#else
	system("read");
#endif
}


/// acquires no error causing user input of integer values 
/// for the purpose of choice selection in a menu. The method 
/// assumes that the value for exit is 0 and returns it if
/// the user input is not in the range between 0
/// and upperRange
int BaseMenu::getChoice(int upperRange)
{
	std::string choiceAsString;
	std::getline(std::cin, choiceAsString);
	for (int i = choiceAsString.size() - 1; i >= 0; i--)
	{
		if (choiceAsString[i]<'0' || choiceAsString[i]>'9')
		{
			choiceAsString.erase(i, 1);
		}
	}

	if (choiceAsString.size() == 0)
		return 0;

	int choice = stoi(choiceAsString);

	if (choice < 0)
		return 0;
	if (upperRange > 0 && choice > upperRange)
		return 0;

	return choice;
}
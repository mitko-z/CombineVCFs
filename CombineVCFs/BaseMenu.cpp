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


int BaseMenu::getChoice()
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

	return stoi(choiceAsString);
}
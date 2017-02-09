#include "StartMenu.h"

void StartMenu::processMenu()
{
	// to do: make at least factory method here
	SelectDirectoryMenu selectDirectory;
	RangeMenu rangeMenu;

	int choice = 0;

	do
	{
		m_sMenuText =
			"Enter your choice :" + NEW_LINE +
			"(1) for Select path to your VCFs (current path is " + selectDirectory.getCurrentDirectory() + ")" + NEW_LINE +
			"(2) for Select range " + "(current range: " + std::to_string(rangeMenu.getLower()) + ":" + std::to_string(rangeMenu.getUpper()) + ")" + NEW_LINE +
			"(3) for Select output path and file name " + NOT_AVAIL_TEXT + NEW_LINE +
			"(4) for Processing data! " + NOT_AVAIL_TEXT + NEW_LINE +
			"(0 or anything else) for Exit" + NEW_LINE;
		printText();
		choice = getChoice(4);

		switch (choice)
		{
		case 1:
			selectDirectory.processMenu();
			break;
		case 2:
			rangeMenu.processMenu();
		}
	}
	while (choice != 0);
}
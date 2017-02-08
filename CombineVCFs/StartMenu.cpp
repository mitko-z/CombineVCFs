#include "StartMenu.h"
#include "SelectDirectoryMenu.h"

void StartMenu::processMenu()
{
	SelectDirectoryMenu selectDirectory;
	int choice = 0;

	do
	{
		m_sMenuText =
			"Enter your choice :" + NEW_LINE +
			"(1) for Select path to your VCFs; current path is " + selectDirectory.getCurrentDirectory() + NEW_LINE +
			"(2) for Select range " + NOT_AVAIL_TEXT + NEW_LINE +
			"(3) for Select output path and file name " + NOT_AVAIL_TEXT + NEW_LINE +
			"(4) for Processing data! " + NOT_AVAIL_TEXT + NEW_LINE +
			"(0) or anything else for Exit" + NEW_LINE;
		printText();
		choice = getChoice();

		switch (choice)
		{
		case 1:
			selectDirectory.processMenu();
			break;

		}
	}
	while (choice != 0);
}
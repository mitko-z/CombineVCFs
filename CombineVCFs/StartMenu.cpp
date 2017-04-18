#include "StartMenu.h"

void StartMenu::processMenu()
{

	// to do: make at least factory method here
	//SelectDirectoryMenu selectDirectory;
	//RangeMenu rangeMenu;
	OpenFilesMenu openFilesMenu;
	OutputFileMenu outputFileMenu;

	int choice = 0;

	do
	{
		// s((const char*)&ws[0], sizeof(wchar_t)/sizeof(char)*ws.size());
		// std::string openFiles (openFilesMenu.getFilesAsWstring().begin(), openFilesMenu.getFilesAsWstring().end());
		std::wstring wOpenFiles = openFilesMenu.getFilesAsWstring();
		std::string openFiles(wOpenFiles.begin(), wOpenFiles.end());
		m_sMenuText =
			"Enter your choice :" + NEW_LINE +
			"(1) for Open/Add your VCF files (currently selected files are " + openFiles + ")" + NEW_LINE +
			"(2) for Select output path and file name " + "(current output file is " + outputFileMenu.getCurrentFileName() + ")" + NEW_LINE +
			"(3) for Processing data! " + NEW_LINE +
			"(0 or anything else) for Exit" + NEW_LINE;
		printText();
		choice = getChoice(3);

		switch (choice)
		{
		case 1:
			openFilesMenu.processMenu();
			break;
		case 2:
			outputFileMenu.processMenu();
			break;
		case 3:
			if (openFilesMenu.getFiles().size() == 0)
			{
				std::cout << "Error! Choose first files to process (choice 1)!" << std::endl;
				pressAnyKey();
			}
			else
			{
				ProcessVCFs processVCFs
					(
						openFilesMenu.getFiles(),
						outputFileMenu.wGetCurrentFileName()
					);
				processVCFs.processIt();
				openFilesMenu.eraseFiles();
				std::cout << "Select new files to process (choice 1) if you need to!" << std::endl;
				pressAnyKey();
			}
			break;
		}
	}
	while (choice != 0);
}
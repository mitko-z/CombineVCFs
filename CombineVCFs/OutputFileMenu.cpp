#include "OutputFileMenu.h"

std::wstring OutputFileMenu::saveFileDialog()
{
	OPENFILENAME ofn;

	WCHAR szFileName[MAX_PATH] = L"";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"txt";

	GetSaveFileName(&ofn);

	return ofn.lpstrFile;
}

void OutputFileMenu::processMenu()
{
	/*int choice = 0;

	do
	{
		m_sMenuText =
			"Enter your choice :" + NEW_LINE +
			"(1) to select output file (current file is " + getCurrentFileName() + ")" + NEW_LINE +
			"(2) Autoload file at program start (current state " + (autoLoadFile ? "Yes" : "No") + ")" + NEW_LINE +
			"(0 or anything else) for Back to Main menu" + NEW_LINE;
		printText();
		choice = getChoice(2);

		switch (choice)
		{
		case 1:*/
			m_wsFileName = saveFileDialog();
	//		break;
	//	case 2:
	//		if (autoLoadFile == true) // switch from true to false and from false to true
	//		{
	//			autoLoadFile = false;
	//		}
	//		else
	//		{
	//			autoLoadFile = true;
	//		}
	//		break;
	//	}
	//} while (choice != 0);

	
}

std::string OutputFileMenu::getCurrentFileName()
{
	return std::string(m_wsFileName.begin(), m_wsFileName.end());
}

std::wstring OutputFileMenu::wGetCurrentFileName()
{
	return m_wsFileName;
}
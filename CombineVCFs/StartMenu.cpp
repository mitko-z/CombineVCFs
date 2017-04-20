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
				processVCFs.processIt(&m_vVCFRecords, &m_vVCFSimilarRecords);
				saveToFile(outputFileMenu.wGetCurrentFileName());
				std::wcout << L"The files" << openFilesMenu.getFilesAsWstring() << L" were successfully processed." << std::endl;
				openFilesMenu.eraseFiles();
				pressAnyKey();
			}
			break;
		}
	}
	while (choice != 0);
}


void StartMenu::saveToFile(std::wstring outputFileName)
{
	std::wofstream outputFile(outputFileName);

	if (!outputFile)
	{
		std::wcerr << L"Could not write to " << outputFileName << std::endl;
		exit(1);
	}

	for each (VCFRecord record in m_vVCFRecords)
	{
		outputFile << L"BEGIN:VCARD" << std::endl;
		outputFile << L"VERSION:3.0" << std::endl;
		for (int i = 0; i < record.fields.size(); i++)
		{
			saveFieldToFile
			(
				outputFile,
				(*record.fields[i]).nameField,
				(*record.fields[i]).getData(),
				(*record.fields[i]).getFormatedData()
			);
		}

		/*outputFile << L"N:" << record.n << std::endl;
		outputFile << L"FN:" << record.fn << std::endl;
		saveFieldToFile(outputFile, L"BDAY", record.bday);
		saveFieldToFile(outputFile, L"NOTE", record.note);
		saveFieldToFile(outputFile, L"ORG", record.org);
		saveFieldToFile(outputFile, L"TITLE", record.title);
		saveFieldToFile(outputFile, L"URL", record.url);
		saveFieldToFile(outputFile, L"X-SKYPE-USERNAME", record.xSkypeUsername);
		saveFieldToFile(outputFile, L"ADR", record.addresses);
		saveFieldToFile(outputFile, L"EMAIL", record.emails);
		saveFieldToFile(outputFile, L"TEL", record.phones);*/
		outputFile << L"END:VCARD" << std::endl;
	}

	std::wcout << L"Records successfully saved to " << outputFileName << L"." << std::endl;

}

void StartMenu::saveFieldToFile(std::wofstream &outputFile, std::wstring fieldName, std::wstring data, std::wstring formatedData)
{
	if ((fieldName == L"N" || fieldName == L"FN") || data != L"")
	{
		outputFile << formatedData;
	}
}
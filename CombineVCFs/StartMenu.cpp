#include "StartMenu.h"

void StartMenu::processMenu()
{

	// to do: make at least factory method here
	OpenFilesMenu openFilesMenu;
	OutputFileMenu outputFileMenu;

	// 1. open previously processed files
	int choice = 0;
	do
	{
		/// wizard style menu

		m_sMenuText =
			"Would you like to load previously processed files?" + NEW_LINE +
			"(1) - Yes, I have a file with already processed files" + NEW_LINE +
			"(2) - Skip" + NEW_LINE +
			"(0 or anything else) - Exit the program" + NEW_LINE;
		printText();
		choice = getChoice(2);

		if (choice == 0)
		{
			exit(0);
		}

		if (choice == 1)
		{
			openFilesMenu.processMenu();

			if (openFilesMenu.getFiles()[0] != L"")
			{
				m_sMenuText = "Please wait . . ." + NEW_LINE;
				printText();
				ProcessVCFs processVCFs;
				processVCFs.processIt
				(
					&m_vVCFRecords,
					&m_vVCFSimilarRecords,
					openFilesMenu.getFiles(),
					false // <-- do not look for duplicates, just load the records
				);
				std::wcout
					<< m_vVCFRecords.size()
					<< L" records from "
					<< openFilesMenu.getFilesAsWstring()
					<< L" were exctracted."
					<< std::endl;

				// saved from before similar records loading
				wstring similarRecordsFileName
				(
					stripExtension(openFilesMenu.getFiles()[0]) +
					SIMILAR_RECORDS_EXT
				);
				std::wifstream similarRecFilesNameCheck;
				similarRecFilesNameCheck.open(similarRecordsFileName, std::ios::out);
				if (similarRecFilesNameCheck.is_open())
				{
					similarRecFilesNameCheck.close();
					processVCFs.processIt
					(
						&m_vVCFSimilarRecords,
						&m_vVCFSimilarRecords,
						similarRecordsFileName,
						false
					);
				}

				openFilesMenu.eraseFiles();
				pressAnyKey();
				choice = 2;
			}
			else
			{
				std::cerr << "Error opening file!" << std::endl;
				m_sMenuText =
					"Would you like to:" + NEW_LINE +
					"(1) Try again -- or --" + NEW_LINE +
					"(2) Skip loading previous records and continue -- or --" + NEW_LINE +
					"(0 or anything else) Exit this program?" + NEW_LINE;
				printText();
				choice = getChoice(2);
				if (choice == 0)
				{
					exit(0);
				}
			}
		}
	} while (choice != 2); // continue

	// 2. select files with records to process
	choice = 0;
	do
	{
		m_sMenuText = 
			"Select file(s) (hold Ctrl key for selecting multiple files) with records to" + NEW_LINE +
			"be processed within the next dialog window!" + NEW_LINE;
		printText();
		pressAnyKey();
		openFilesMenu.processMenu();
		if (openFilesMenu.getFiles()[0] == L"")
		{
			m_sMenuText = "Error loading files!" + NEW_LINE +
				"Would you like to" + NEW_LINE +
				"(1) - Try again" + NEW_LINE +
				"(0 or anything else) - Exit from this program?" + NEW_LINE;
			printText();
			choice = getChoice(1);
			if (choice == 0)
			{
				exit(0);
			}
			else
			{
				openFilesMenu.eraseFiles();
			}
		}
		else
		{
			choice = 2;
		}
	} while (choice != 2);

	// 3. select where the records to be saved
	m_sMenuText = "Select where the new records to be saved in the next dialog window!" + NEW_LINE;
	printText();
	pressAnyKey();
	outputFileMenu.processMenu();

	// 4. show info before processing data
	choice = 0;
	std::wstring wOpenFiles(openFilesMenu.getFilesAsWstring());
	std::string openFiles(wOpenFiles.begin(), wOpenFiles.end());
	m_sMenuText =
		"Review the information below before start of processing the new records:" + NEW_LINE +
		NEW_LINE +
		std::to_string(m_vVCFRecords.size()) + " records were loaded previously;" + NEW_LINE +
		"the files " + openFiles + " were selected new records to be ecstracted from;" + NEW_LINE +
		"in " + outputFileMenu.getCurrentFileName() + " was selected the processed records to be saved in." + NEW_LINE +
		NEW_LINE +
		"Is this information correct? Select:" + NEW_LINE +
		"(1) - to continue with proceesing" + NEW_LINE +
		"(0 or anything else - for Exit" + NEW_LINE;
	printText();
	choice = getChoice(1);
	if (choice == 0)
	{
		exit(0);
	}

	// 5. Process the new records
	if (openFilesMenu.getFiles()[0] == L"")
	{
		m_sMenuText = "Error: Can't read files with new records!";
		printText();
		pressAnyKey();
		exit(1);
	}
	else
	{
		m_sMenuText = "Please wait . . .";
		printText();
		ProcessVCFs processVCFs;
		processVCFs.processIt
		(
			&m_vVCFRecords,
			&m_vVCFSimilarRecords,
			openFilesMenu.getFiles()
		);

		// 5. save the records
		saveToFile(outputFileMenu.wGetCurrentFileName(), m_vVCFRecords);
		// save the similar records for later use with the same name but with the smr extension
		wstring similarRecordsFileName
		(
			stripExtension(outputFileMenu.wGetCurrentFileName()) +
			SIMILAR_RECORDS_EXT
		);
		saveToFile(similarRecordsFileName, m_vVCFSimilarRecords);

		m_sMenuText = "The files" + std::string(openFilesMenu.getFilesAsWstring().begin(), openFilesMenu.getFilesAsWstring().end()) + " were successfully processed." + NEW_LINE;
		printText();
		openFilesMenu.eraseFiles();
		pressAnyKey();
	}
	///

	//do
	//{
	//	// s((const char*)&ws[0], sizeof(wchar_t)/sizeof(char)*ws.size());
	//	// std::string openFiles (openFilesMenu.getFilesAsWstring().begin(), openFilesMenu.getFilesAsWstring().end());
	//	std::wstring wOpenFiles(openFilesMenu.getFilesAsWstring());
	//	std::string openFiles(wOpenFiles.begin(), wOpenFiles.end());
	//	m_sMenuText =
	//		"Enter your choice :" + NEW_LINE +
	//		"(1) for Open previously processed data" + NEW_LINE +
	//		"(2) for Open/Add your VCF files (currently selected files are " + openFiles + ")" + NEW_LINE +
	//		"(3) for Select output path and file name " + "(current output file is " + outputFileMenu.getCurrentFileName() + ")" + NEW_LINE +
	//		"(4) for Process data! " + NEW_LINE +
	//		"(0 or anything else) for Exit" + NEW_LINE;
	//	printText();
	//	choice = getChoice(4);

	//	switch (choice)
	//	{
	//	case 1:
	//		{
	//			openFilesMenu.processMenu();
	//			ProcessVCFs processVCFs;
	//			processVCFs.processIt
	//				(
	//					&m_vVCFRecords, 
	//					&m_vVCFSimilarRecords, 
	//					openFilesMenu.getFiles(),
	//					false // <-- do not look for duplicates, just load the records
	//				);
	//			std::wcout 
	//				<< m_vVCFRecords.size()
	//				<< L" records from " 
	//				<< openFilesMenu.getFilesAsWstring() 
	//				<< L" were exctracted." 
	//				<< std::endl;

	//			// saved from before similar records loading
	//			wstring similarRecordsFileName
	//			(
	//				stripExtension(openFilesMenu.getFiles()[0]) +
	//				SIMILAR_RECORDS_EXT
	//			);
	//			std::wifstream similarRecFilesNameCheck;
	//			similarRecFilesNameCheck.open(similarRecordsFileName, std::ios::out);
	//			if (similarRecFilesNameCheck.is_open())
	//			{
	//				similarRecFilesNameCheck.close();
	//				processVCFs.processIt
	//					(
	//						&m_vVCFSimilarRecords,
	//						&m_vVCFSimilarRecords,
	//						similarRecordsFileName,
	//						false
	//					);
	//			}
	//			
	//			openFilesMenu.eraseFiles();
	//			pressAnyKey();
	//			break;
	//		}
	//	case 2:
	//		openFilesMenu.processMenu();
	//		break;
	//	case 3:
	//		outputFileMenu.processMenu();
	//		break;
	//	case 4:
	//		if (openFilesMenu.getFiles().size() == 0)
	//		{
	//			std::cout << "Error! Choose first files to process (choice 1)!" << std::endl;
	//			pressAnyKey();
	//		}
	//		else
	//		{
	//			ProcessVCFs processVCFs;
	//			processVCFs.processIt
	//			(
	//				&m_vVCFRecords,
	//				&m_vVCFSimilarRecords,
	//				openFilesMenu.getFiles()
	//			);

	//			//// save procedures ////
	//			// save the records
	//			saveToFile(outputFileMenu.wGetCurrentFileName(), m_vVCFRecords);
	//			// save the similar records for later use with the same name but with the smr extension
	//			wstring similarRecordsFileName
	//					(
	//						stripExtension(outputFileMenu.wGetCurrentFileName()) + 
	//						SIMILAR_RECORDS_EXT
	//					);
	//			saveToFile(similarRecordsFileName, m_vVCFSimilarRecords);

	//			std::wcout << L"The files" << openFilesMenu.getFilesAsWstring() << L" were successfully processed." << std::endl;
	//			openFilesMenu.eraseFiles();
	//			pressAnyKey();
	//		}
	//		break;
	//	}
	//}
	//while (choice != 0);
}


void StartMenu::saveToFile(std::wstring outputFileName, std::vector<VCFRecord> records)
{
	std::wofstream outputFile(outputFileName);

	if (!outputFile)
	{
		std::wcerr << L"Could not write to " << outputFileName << std::endl;
		exit(1);
	}

	for each (VCFRecord record in records)
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

std::wstring StartMenu::stripExtension(const std::wstring fileName)
{
	if (fileName.find(L"."))
	{
		std::wstring newFileName = fileName;
		for (int i = newFileName.size() - 1; i >= 0; i--)
		{
			if (newFileName[i] == L'.')
			{
				return newFileName;
			}
			newFileName.resize(newFileName.size() - 1);
		}
	}
	else
	{
		return fileName;
	}
}
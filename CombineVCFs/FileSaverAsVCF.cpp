#include "FileSaverAsVCF.h"

void FileSaverAsVCF::saveToFile()
{

	std::wofstream outputFile(fileName);

	if (!outputFile)
	{
		std::wcerr << L"Could not write to " << fileName << std::endl;
		exit(1);
	}

	for each (auto& record in this->records)
	{
		outputFile << L"BEGIN:VCARD" << std::endl;
		outputFile << L"VERSION:3.0" << std::endl;
		for (int i = 0; i < record.second.fields.size(); i++)
		{
			saveFieldToFile
			(
				outputFile,
				(*record.second.fields[i]).getName(),
				(*record.second.fields[i]).getData(),
				(*record.second.fields[i]).getFormatedData()
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

	std::wcout << L"Records successfully saved to " << fileName << L"." << std::endl;

}

void FileSaverAsVCF::saveFieldToFile(std::wofstream &outputFile, std::wstring fieldName, std::wstring data, std::wstring formatedData)
{
	if ((fieldName == L"N" || fieldName == L"FN") || data != L"")
	{
		outputFile << formatedData;
	}
}
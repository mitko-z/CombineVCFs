#include "VCFReader3_0.h"

vector<VCFRecord>& VCFReader3_0::loadVCFRecordsFromFile(vector<VCFRecord>& records, 
	                                                    std::wstring pathToFile)
{
	std::wifstream inputFile;
	inputFile.open(pathToFile, std::ios::in);
	if (!inputFile.is_open())
	{
		std::cerr << "Error! Unable to open this file: " << std::endl;
		std::wcout << pathToFile << std::endl;
		exit(1);
	}

	std::wstring contents;
	VCFRecord *aRecord;

	while (!inputFile.eof())
	{
		aRecord = new VCFRecord;
		std::getline(inputFile, contents); // read 1st line = BEGIN:VCARD
		std::getline(inputFile, contents); // read 2nd line = VERSION:3.0
		std::getline(inputFile, contents); // read 1st formatedField of record

		if (contents != L"")
			do
			{
				std::wstring criteria = L"";
				for (int i = 0; contents[i] != L':' && contents[i] != L';' && i < contents.size(); i++)
				{
					criteria += contents[i];
				}
				std::wstring type = L"";
				int lenghtOfType = 0;
				if (contents[criteria.length()] == L';')
				{
					lenghtOfType = 6; // <-- this the lenght of L";TYPE="
					for (int i = criteria.length() + lenghtOfType; contents[i] != L':'; i++)
					{
						type += contents[i];
					}
				}
				std::wstring data = L"";
				//      i = criteria lenght + length of ";TYPE=" + type lenght + leght of ":"
				for (int i = criteria.length() + lenghtOfType + type.length() + 1; i < contents.length(); i++)
				{
					data += contents[i];
				}
				// std::wcout << data << std::endl;
				aRecord->insertData(criteria, data, type);
				std::getline(inputFile, contents);
			} while (contents != L"END:VCARD");

			records.push_back(*aRecord);
			delete aRecord;
			aRecord = nullptr;
	}

	inputFile.close();
	return records;
}
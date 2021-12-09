#include "FileReaderFromVCFs.h"

void FileReaderFromVCFs::loadRecords(std::map<long long, VCFRecord>& records)
{

	std::wifstream inputFile;
	inputFile.open(this->fileName, std::ios::in);
	if (!inputFile.is_open())
	{
		std::cerr
			<< "Error! Unable to open this file:"
			<< std::string(this->fileName.begin(), this->fileName.end())
			<< std::endl;
		exit(1);
	}

	std::wstring lineFromFile;
	std::getline(inputFile, lineFromFile); // read 1st line = BEGIN:VCARD
	std::getline(inputFile, lineFromFile); // read 2nd line = VERSION...
	inputFile.close();
	VCFReader *reader = nullptr;
	try
	{
		reader = VCFReader::makeVCFReader(lineFromFile);
	}
	catch (const char *errorMessage)
	{
		std::cerr << L" ERROR: " << errorMessage << std::endl;
		exit(1);
	}

	reader->loadVCFRecordsFromFile(records, this->fileName);

	//	std::getline(inputFile, lineFromFile); // read 1st formatedField of record
	//	if(lineFromFile!=L"")
	//		do
	//		{
	//			std::wstring criteria = L"";
	//			for (int i = 0; lineFromFile[i] != L':' && lineFromFile[i] != L';' && i < lineFromFile.size(); i++)
	//			{
	//				criteria += lineFromFile[i];
	//			}
	//			std::wstring type = L"";
	//			int lenghtOfType = 0;
	//			if (lineFromFile[criteria.length()] == L';')
	//			{
	//				lenghtOfType = 6; // <-- this the lenght of L";TYPE="
	//				for (int i = criteria.length() + lenghtOfType; lineFromFile[i] != L':'; i++)
	//				{
	//					type += lineFromFile[i];
	//				}
	//			}
	//			std::wstring data = L"";
	//			//      i = criteria lenght + length of ";TYPE=" + type lenght + leght of ":"
	//			for (int i = criteria.length() + lenghtOfType + type.length() + 1; i < lineFromFile.length(); i++)
	//			{
	//				data += lineFromFile[i];
	//			}
	//			// std::wcout << data << std::endl;
	//			aRecord->insertData(criteria, data, type);
	//			std::getline(inputFile, lineFromFile);
	//		} while (lineFromFile != L"END:VCARD");
	//	records.push_back(*aRecord);
	//	delete aRecord;
	//	aRecord = nullptr;
	//}
	//inputFile.close();

	if (reader)
	{
		delete[] reader;
		reader = nullptr;
	}
}
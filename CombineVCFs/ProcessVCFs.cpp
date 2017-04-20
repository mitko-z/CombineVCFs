#include "ProcessVCFs.h"

std::vector<VCFRecord> ProcessVCFs::loadVCFRecordsFromFile(std::wstring pathToFile)
{
	std::wifstream inputFile;
	inputFile.open(pathToFile, std::ios::in);
	if (!inputFile.is_open())
	{
		std::cerr << "Error! Unable to open this file:" << std::endl;
		std::wcout << pathToFile << std::endl;
		exit(1);
	}

	std::wstring contents;
	VCFRecord *aRecord;
	std::vector<VCFRecord> records;

	while (!inputFile.eof())
	{
		aRecord = new VCFRecord;
		std::getline(inputFile, contents); // read 1st line = BEGIN:VCARD
		std::getline(inputFile, contents); // read 2nd line = VERSION:3.0
		std::getline(inputFile, contents); // read 1st formatedField of record

		if(contents!=L"")
			do
			{

				std::wstring criteria = L"";
				for (int i = 0; contents[i] != L':' && contents[i] != L';' && i < contents.size(); i++)
				{
					criteria += contents[i];
				}
				std::wstring type = L"";
				int typePrefix = 0;
				if (contents[criteria.length()] == L';')
				{
					typePrefix = 6; // this the lenght of L";TYPE="
					for (int i = criteria.length() + typePrefix; contents[i] != L':'; i++)
					{
						type += contents[i];
					}
				}
				std::wstring data = L"";
				//      i = criteria lenght + length of L";TYPE= + type lenght + leght of L":"
				for (int i = criteria.length() + typePrefix + type.length() + 1; i < contents.length(); i++)
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

void ProcessVCFs::processIt(std::vector<VCFRecord> *VCFRecords, std::vector<VCFRecord> *similarVCFRecords)
{
	//std::wstring pathToFile = getPathToVCF(m_uiLowerRange);
	*VCFRecords = loadVCFRecordsFromFile(m_vwsInputFiles[0]);
	
	for (int i = 1; i < m_vwsInputFiles.size(); i++)
	{
		std::vector<VCFRecord> newRecords = loadVCFRecordsFromFile(m_vwsInputFiles[i]);
		for (int j = 0; j < newRecords.size(); j++)
		{
			bool toAddNewRecord = true;
			//for each(auto record in m_vVCFRecords)
			for (int k = 0; k < VCFRecords->size(); k++)
			{
				if 
					(
						(VCFRecords->at(k) == newRecords[j]) ||
						(isFoundInSimilarRecords(newRecords[j], *similarVCFRecords))
					)
				{
					toAddNewRecord = false;
					break;	// this record is identical with another one =>
							// no need to go through the rest of the records
				}
				else
				{
					if (newRecords[j].isSimilarTo(VCFRecords->at(k)))
					{
						similarVCFRecords->push_back(newRecords[j]);
						SimilarRecordsMenu similarRecordsMenu(VCFRecords->at(k), newRecords[j]);
						similarRecordsMenu.processMenu();
						switch (similarRecordsMenu.actionTaken)
						{
						case SimilarRecordsMenu::actionType::add: // insertData both records
							toAddNewRecord = true;
							break;
						case SimilarRecordsMenu::actionType::merge: // make one record from these two
							toAddNewRecord = false;
							VCFRecords->at(k).mergeData(newRecords[j]);
							break;
						case SimilarRecordsMenu::actionType::replace: // delete old, insertData new
							toAddNewRecord = true;
							similarVCFRecords->push_back(VCFRecords->at(k));
							VCFRecords->erase(VCFRecords->begin() + k);
							break;
						case SimilarRecordsMenu::actionType::skip: // skip adding the new record
							toAddNewRecord = false; 
							break;
						}
						break; // similar records found => break for loop
					}
				}
			}
			if (toAddNewRecord)
			{
				VCFRecords->push_back(newRecords[j]);
			}
		}
	}
	
	
}

//std::wstring ProcessVCFs::getPathToVCF(unsigned int number)
//{
//	ostringstream ss;
//	ss << setw(5) << setfill('0') << number;
//	std::string numberWithZeros = ss.str();
//	std::wstring wNumberWithZeros(numberWithZeros.begin(), numberWithZeros.end());
//	return m_sInputDirectory + L"\\" + wNumberWithZeros + L".vcf";
//}



bool ProcessVCFs::isFoundInSimilarRecords(VCFRecord recordToCheck, std::vector<VCFRecord> similarVCFRecords)
{
	for each (VCFRecord similarRecord in similarVCFRecords)
	{
		if (recordToCheck == similarRecord)
		{
			return true;
		}
	}
	return false;
}

//void ProcessVCFs::saveFieldToFile(std::wofstream &outputFile, std::wstring fieldsName, vector<pair<wstring, wstring>> fields)
//{
//	for each(pair<wstring, wstring> field in fields)
//	{
//		outputFile << fieldsName << L";TYPE=" << field.first << ":" << field.second << std::endl;
//	}
//}
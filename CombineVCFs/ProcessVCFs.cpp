#include "ProcessVCFs.h"

std::vector<VCFRecord> ProcessVCFs::loadVCFFile(std::wstring pathToFile)
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
		std::getline(inputFile, contents); // read 1st field of record

		if(contents!=L"")
			do
			{

				// std::wcout << contents << std::endl;
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

void ProcessVCFs::processIt()
{
	m_vVCFRecords = loadVCFFile(getPathToVCF(m_uiLowerRange));
	for (int i = m_uiLowerRange + 1; i <= m_uiUpperRange; i++)
	{
		std::vector<VCFRecord> newRecords = loadVCFFile(getPathToVCF(i));
		for (int j = 0; j < newRecords.size(); j++)
		{
			bool toAddNewRecord = true;
			//for each(auto record in m_vVCFRecords)
			for (int k = 0; k < m_vVCFRecords.size(); k++)
			{
				if (m_vVCFRecords[k] == newRecords[j])
				{
					toAddNewRecord = false;
					break;	// this record is identical with another one =>
							// no need to go through the rest of the records
				}
				else
				{
					if (newRecords[j].isSimilarTo(m_vVCFRecords[k]))
					{
						// TODO ask user what to do - merge, use new, add both
						SimilarRecordsMenu similarRecordsMenu(m_vVCFRecords[k], newRecords[j]);
						similarRecordsMenu.processMenu();
						switch (similarRecordsMenu.actionTaken)
						{
						case SimilarRecordsMenu::actionType::add: // add both records
							toAddNewRecord = true;
							break;
						case SimilarRecordsMenu::actionType::merge: // make one record from these two
							toAddNewRecord = false;
							m_vVCFRecords[k].mergeData(newRecords[j]);
							break;
						case SimilarRecordsMenu::actionType::replace: // delete old, add new
							toAddNewRecord = true;
							m_vVCFRecords.erase(m_vVCFRecords.begin() + k);
							break;
						case SimilarRecordsMenu::actionType::skip: // skip adding the new record
							toAddNewRecord = false; 
							break;
						}
						break; // similar records  found -> break for loop
					}
				}
			}
			if (toAddNewRecord)
			{
				m_vVCFRecords.push_back(newRecords[j]);
			}
		}
	}
	
}

std::wstring ProcessVCFs::getPathToVCF(unsigned int number)
{
	ostringstream ss;
	ss << setw(5) << setfill('0') << number;
	std::string numberWithZeros = ss.str();
	std::wstring wNumberWithZeros(numberWithZeros.begin(), numberWithZeros.end());
	return m_sInputDirectory + L"\\" + wNumberWithZeros + L".vcf";
}
#include "ProcessVCFs.h"

std::vector<VCFRecord> ProcessVCFs::loadVCFRecordsFromFile(std::wstring pathToFile)
{
	std::wifstream inputFile;
	inputFile.open(pathToFile, std::ios::in);
	if (!inputFile.is_open())
	{
		std::cerr 
			<< "Error! Unable to open this file:" 
			<< std::string(pathToFile.begin(), pathToFile.end()) 
			<< std::endl;
		exit(1);
	}

	std::wstring lineFromFile;
	//VCFRecord *aRecord;
	//while (!inputFile.eof())
	//{
	//	aRecord = new VCFRecord;
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
	
	std::vector<VCFRecord> records(reader->loadVCFRecordsFromFile(pathToFile));

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

	return records;
}

void ProcessVCFs::processIt
			(
				std::vector<VCFRecord> *VCFRecords,
				std::vector<VCFRecord> *similarVCFRecords,
				std::vector<std::wstring> inputFiles,
				bool lookForDublicates
			)
{
	m_vwsInputFiles = inputFiles;
	m_bLookForDublicates = lookForDublicates;

	int startFromFile = 1;
	//std::wstring pathToFile = getPathToVCF(m_uiLowerRange);
	if (VCFRecords->size() == 0)
	{
		*VCFRecords = loadVCFRecordsFromFile(m_vwsInputFiles[0]);
	}
	else
	{
		startFromFile = 0;
	}
	
	for (int i = startFromFile; i < m_vwsInputFiles.size(); i++)
	{
		std::vector<VCFRecord> newRecords(loadVCFRecordsFromFile(m_vwsInputFiles[i]));
		for (int j = 0; j < newRecords.size(); j++)
		{
			bool toAddNewRecord = true;
			
			if (m_bLookForDublicates)
			{
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

							////write at the field with criteria "SIMILAR" that this is simialr record
							//for each
							//	(
							//		auto field 
							//		in 
							//		similarVCFRecords->at(similarVCFRecords->size() - 1).fields
							//	)
							//{
							//	if (field->nameField == L"SIMILAR")
							//	{
							//		field->insertData(L"YES", L"");
							//		break;
							//	}
							//}

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
			}
			if (toAddNewRecord)
			{
				VCFRecords->push_back(newRecords[j]);
			}
		}
	}
	
	
}

void ProcessVCFs::processIt
(
	std::vector<VCFRecord> *VCFRecords,
	std::vector<VCFRecord> *similarVCFRecords,
	std::wstring inputFile,
	bool lookForDublicates
)
{
	std::vector<wstring> vectorForSingleFile;
	vectorForSingleFile.push_back(inputFile);
	processIt(VCFRecords, similarVCFRecords, vectorForSingleFile, lookForDublicates);
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
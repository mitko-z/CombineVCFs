#pragma once
#include "VCFRecord.h"
#include "SimilarRecordsMenu.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream> // files
#include <cstdlib> // for exit()
#include <locale> // unicode chars and strings
//#include <iomanip> // for setw() and setfill()
#include <sstream> // for std::ostringstream

class ProcessVCFs
{
private:
	/*std::wstring m_sInputDirectory;
	unsigned int m_uiLowerRange;
	unsigned int m_uiUpperRange;*/
	std::vector<std::wstring> m_vwsInputFiles;
	std::wstring m_sOutputFile;
	std::vector<VCFRecord> m_vVCFRecords;
	std::vector<VCFRecord> m_vVCFSimilarRecords;
	

	ProcessVCFs() {} // no default constructor allowed

	std::vector<VCFRecord> loadVCFRecordsFromFile(std::wstring pathToFile);

	void saveToFile();

	void saveFieldToFile(std::wofstream &outputFile, std::wstring fieldName, std::wstring data, std::wstring formatedData);

	bool isFoundInSimilarRecords(VCFRecord recordToCheck);

	//std::wstring getPathToVCF(unsigned int number);
	//void saveFieldToFile(std::wofstream &outputFile, std::wstring fieldsName, vector<pair<wstring, wstring>> fields);

public:
	ProcessVCFs
		(
			/*std::wstring inputDirectory, 
			unsigned int lowerRange, 
			unsigned int upperRange,*/ 
			std::vector<std::wstring> inputFiles,
			std::wstring outputFile
		):
		/*m_sInputDirectory(inputDirectory),
		m_uiLowerRange(lowerRange),
		m_uiUpperRange(upperRange),*/
		m_vwsInputFiles(inputFiles),
		m_sOutputFile(outputFile)
	{}

	void processIt();

};
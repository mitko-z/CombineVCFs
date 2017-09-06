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
	/*std::vector<VCFRecord> m_vVCFRecords;
	std::vector<VCFRecord> m_vVCFSimilarRecords;*/

	bool m_bLookForDublicates;

	std::vector<VCFRecord> loadVCFRecordsFromFile(std::wstring pathToFile);

	bool isFoundInSimilarRecords(VCFRecord recordToCheck, std::vector<VCFRecord> similarVCFRecords);

	//std::wstring getPathToVCF(unsigned int number);
	//void saveFieldToFile(std::wofstream &outputFile, std::wstring fieldsName, vector<pair<wstring, wstring>> fields);

public:
	//ProcessVCFs
	//	(
	//		/*std::wstring inputDirectory, 
	//		unsigned int lowerRange, 
	//		unsigned int upperRange,*/ 
	//		std::vector<std::wstring> inputFiles,
	//		bool m_bLookForDublicates = true
	//	):
	//	/*m_sInputDirectory(inputDirectory),
	//	m_uiLowerRange(lowerRange),
	//	m_uiUpperRange(upperRange),*/
	//	m_vwsInputFiles(inputFiles),
	//	m_bLookForDublicates(m_bLookForDublicates)
	//{}

	ProcessVCFs(bool lookForDublicates = true) 
		:m_bLookForDublicates(lookForDublicates)
	{}

	void processIt
			(
				std::vector<VCFRecord> *VCFRecords, 
				std::vector<VCFRecord> *similarVCFRecords,
				std::vector<std::wstring> inputFiles,
				bool lookForDublicates = true
			);
	void processIt
			(
				std::vector<VCFRecord> *VCFRecords,
				std::vector<VCFRecord> *similarVCFRecords,
				std::wstring inputFile,
				bool lookForDublicates = true
			);

};
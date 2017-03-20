#pragma once
#include "VCFRecord.h"
#include "SimilarRecordsMenu.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream> // files
#include <cstdlib> // for exit()
#include <locale> // unicode chars and strings
#include <iomanip> // for setw() and setfill()
#include <sstream> // for std::ostringstream

class ProcessVCFs
{
private:
	std::wstring m_sInputDirectory;
	unsigned int m_uiLowerRange;
	unsigned int m_uiUpperRange;
	std::wstring m_sOutputFile;
	std::vector<VCFRecord> m_vVCFRecords;
	

	ProcessVCFs() {} // no default constructor allowed

	std::vector<VCFRecord> loadVCFFile(std::wstring pathToFile);

	std::wstring getPathToVCF(unsigned int number);

public:
	ProcessVCFs
		(
			std::wstring inputDirectory, 
			unsigned int lowerRange, 
			unsigned int upperRange, 
			std::wstring outputFile
		):
		m_sInputDirectory(inputDirectory),
		m_uiLowerRange(lowerRange),
		m_uiUpperRange(upperRange),
		m_sOutputFile(outputFile)
	{}

	void processIt();

};
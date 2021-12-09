#pragma once

#include <iostream> // info 
#include <locale>	// wide char strings operations
#include <fstream>	// output save to 
#include <vector>   // vector with records
#include "VCFRecord.h"

class FileSaver
{
protected:
	std::wstring fileName;
	std::map<long long, VCFRecord> records;
	virtual void saveFieldToFile(std::wofstream &outputFile, std::wstring fieldName, std::wstring data, std::wstring formatedData) = 0;
public:
	FileSaver(std::wstring outputFileName, const std::map<long long, VCFRecord> & recordsToSave) :
		fileName(outputFileName),
		records(recordsToSave)
	{}

	virtual void saveToFile() = 0;
	void setFileName(std::wstring outputFileName) { fileName = outputFileName; }
	void setRecords(const std::map<long long, VCFRecord> & recordsToSave) { records = recordsToSave; }
};
#pragma once

#include <locale>		// wstring
#include <vector>		// vector of...
#include "VCFRecord.h"	// ...VCF records

class FileReader
{
protected:
	std::wstring fileName;
	std::vector<VCFRecord> records;
public:
	FileReader(std::wstring pathToFileToReadFrom) : fileName(pathToFileToReadFrom) {}
	void setFileName(std::wstring pathToFileToReadFrom) { this->fileName = pathToFileToReadFrom; }
	std::vector<VCFRecord>& getCurrentRecords() { return records; }
	virtual std::vector<VCFRecord>& loadRecords(std::vector<VCFRecord>& records) = 0;
};
#pragma once

#include <fstream> // files
#include <locale> // unicode chars and strings
#include <cstdlib> // for exit()
#include <vector> // vector of VCFRecords
#include "VCFRecord.h"


class VCFReader 
{
public:
	static VCFReader *makeVCFReader(std::wstring version); // factory method
	virtual vector<VCFRecord> loadVCFRecordsFromFile(std::wstring pathToFile) = 0;
};
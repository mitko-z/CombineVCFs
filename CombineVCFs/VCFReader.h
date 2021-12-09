#pragma once

#include <fstream> // files
#include <locale> // unicode chars and strings
#include <cstdlib> // for exit()
#include <map> // map of (hash of VCFRecord, VCFRecord)-s 
#include "VCFRecord.h"


class VCFReader 
{
public:
	static VCFReader *makeVCFReader(std::wstring version); // factory method
	virtual void loadVCFRecordsFromFile(map<long long, VCFRecord>& records, 
										std::wstring pathToFile) = 0;
};
#pragma once
#include "VCFReader.h"

class VCFReader2_1 : public VCFReader
{
	void loadVCFRecordsFromFile(map<long long, VCFRecord>& records, 
								std::wstring pathToFile) override;
};
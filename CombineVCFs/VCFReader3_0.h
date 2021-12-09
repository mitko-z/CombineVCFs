#pragma once

#include "VCFReader.h"

class VCFReader3_0 : public VCFReader
{
	void loadVCFRecordsFromFile(map<long long, VCFRecord>& records, 
								std::wstring pathToFile) override;
};
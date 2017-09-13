#pragma once

#include "VCFReader.h"

class VCFReader3_0 : public VCFReader
{
	virtual vector<VCFRecord> loadVCFRecordsFromFile(std::wstring pathToFile);
};
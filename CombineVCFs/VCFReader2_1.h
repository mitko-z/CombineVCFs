#pragma once
#include "VCFReader.h"

class VCFReader2_1 : public VCFReader
{
	virtual std::vector<VCFRecord> loadVCFRecordsFromFile(std::wstring pathToFile);
};
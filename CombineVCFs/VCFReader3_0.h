#pragma once

#include "VCFReader.h"

class VCFReader3_0 : public VCFReader
{
	virtual vector<VCFRecord>& loadVCFRecordsFromFile(vector<VCFRecord>& records, 
		                                              std::wstring pathToFile);
};
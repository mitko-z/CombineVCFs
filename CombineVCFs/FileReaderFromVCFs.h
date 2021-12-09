#pragma once

#include "FileReader.h"
#include "VCFReader.h"

class FileReaderFromVCFs : public FileReader
{
public:
	FileReaderFromVCFs(std::wstring pathToFileToReadFrom) : FileReader(pathToFileToReadFrom) {}
	void loadRecords(std::map<long long, VCFRecord>& records) override;
};
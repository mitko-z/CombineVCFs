#pragma once

#include "FileReader.h"
#include "VCFReader.h"

class FileReaderFromVCFs : public FileReader
{
public:
	FileReaderFromVCFs(std::wstring pathToFileToReadFrom) : FileReader(pathToFileToReadFrom) {}
	std::vector<VCFRecord>& loadRecords(std::vector<VCFRecord>& records);
};
#pragma once

#include "FileSaver.h"

class FileSaverAsVCF : public FileSaver
{
private:
	void saveFieldToFile(std::wofstream &outputFile, std::wstring fieldName, std::wstring data, std::wstring formatedData);
public:
	FileSaverAsVCF(std::wstring outputFileName, const std::vector<VCFRecord> & recordsToSave)
		: FileSaver(outputFileName, recordsToSave)
	{	}

	void saveToFile();
};
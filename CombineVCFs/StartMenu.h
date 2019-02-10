#pragma once
#include "BaseMenu.h"
//#include "SelectDirectoryMenu.h"
//#include "RangeMenu.h"
#include "OpenFilesMenu.h"
#include "OutputFileMenu.h"
#include "ProcessVCFs.h"
#include "VCFRecord.h"
#include "FileSaverAsVCF.h"
#include <vector> // vector of VCF Records
#include <string> // operator+ overload


class StartMenu : public BaseMenu
{
private:

	// constant texts
	const std::string NOT_AVAIL_TEXT = "(UNDER CONSTRUCTION. Please be patient!)";
	const std::wstring SIMILAR_RECORDS_EXT = L"smr";

	std::vector<VCFRecord> m_vVCFRecords;
	std::vector<VCFRecord> m_vVCFSimilarRecords;

	void saveToFile(std::wstring outputFile, std::vector<VCFRecord> records);

	void saveFieldToFile(std::wofstream &outputFile, std::wstring fieldName, std::wstring data, std::wstring formatedData);

	std::wstring stripExtension(std::wstring fileName);

public:
	StartMenu() : BaseMenu("") {}
	void processMenu();
};
#pragma once
#include "BaseMenu.h"
//#include "SelectDirectoryMenu.h"
//#include "RangeMenu.h"
#include "OpenFilesMenu.h"
#include "OutputFileMenu.h"
#include "ProcessVCFs.h"
#include "VCFRecord.h"
#include <vector> // vector of VCF Records
#include <string> // +operator overload


class StartMenu : public BaseMenu
{
private:
	const std::string NOT_AVAIL_TEXT = "(UNDER CONSTRUCTION. Please be patient!)";
	std::vector<VCFRecord> m_vVCFRecords;
	std::vector<VCFRecord> m_vVCFSimilarRecords;

	void saveToFile(std::wstring outputFile);

	void saveFieldToFile(std::wofstream &outputFile, std::wstring fieldName, std::wstring data, std::wstring formatedData);

public:
	StartMenu() : BaseMenu("") {}
	void processMenu();
};
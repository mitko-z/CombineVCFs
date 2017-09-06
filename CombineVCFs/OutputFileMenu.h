#pragma once

#include "BaseMenu.h"
#include <string>
#include <Windows.h>
#include <iostream>  //debug info

class OutputFileMenu : public BaseMenu
{
public:
	OutputFileMenu() :m_wsFileName(L"C:\\CombinedVCFs.txt"), autoLoadFile(false) {}
	OutputFileMenu(std::wstring fileName, bool autoLoadFile) : m_wsFileName(fileName), autoLoadFile(autoLoadFile) {}
	void processMenu();
	std::string getCurrentFileName();
	std::wstring wGetCurrentFileName();
	bool autoLoadFile;

private:
	std::wstring m_wsFileName;
	std::wstring saveFileDialog();
};
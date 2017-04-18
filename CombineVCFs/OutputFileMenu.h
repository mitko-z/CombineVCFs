#pragma once

#include "BaseMenu.h"
#include <string>
#include <Windows.h>
#include <iostream>  //debug info

class OutputFileMenu : public BaseMenu
{
public:
	OutputFileMenu() :m_wsFileName(L"C:\\CombinedVCFs.txt") {}
	OutputFileMenu(std::wstring fileName) : m_wsFileName(fileName) {}
	void processMenu();
	std::string getCurrentFileName();
	std::wstring wGetCurrentFileName();

private:
	std::wstring m_wsFileName;
	std::wstring saveFileDialog();
};
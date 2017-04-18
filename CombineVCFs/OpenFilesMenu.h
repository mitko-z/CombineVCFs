#pragma once

#include "BaseMenu.h"
#include <Windows.h>	// open file dialog functions
#include <locale>		// wide char strings operations
#include <vector>		// vector with names of files
#include <iostream> // debug


class OpenFilesMenu : public BaseMenu
{
private:
	const std::wstring NONE_SELECTED_TEXT;
	std::vector<std::wstring> m_vwsFiles;
	std::wstring m_wsFilesAsString;

	void openFilesDialog();

	void pushToFields(std::vector<std::wstring> filesToPush);
public:
	OpenFilesMenu() : 
		NONE_SELECTED_TEXT(L"- None selected -"),
		m_wsFilesAsString(NONE_SELECTED_TEXT) {}
	std::vector<std::wstring> getFiles() { return m_vwsFiles; }
	std::wstring getFilesAsWstring() { return m_wsFilesAsString; }

	void eraseFiles();

	void processMenu();
};
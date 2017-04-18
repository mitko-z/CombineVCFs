#pragma once
#include "BaseMenu.h"
#include <windows.h>
#include <string>
#include <shlobj.h>
#include <iostream>
#include <sstream>
#include <vector>

#pragma comment(lib, "shell32.lib")

class SelectDirectoryMenu : public BaseMenu
{
private:
	std::wstring m_wsCurrentDirectory;

	std::wstring BrowseFolder(std::wstring saved_path);

public:

	SelectDirectoryMenu();

	void processMenu();

	std::string getCurrentDirectory();

	std::wstring wGetCurrentDirectory();

	static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

};
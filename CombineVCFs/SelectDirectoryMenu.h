#pragma once
#include "BaseMenu.h"
#include <windows.h>
#include <string>
#include <shlobj.h>
#include <iostream>
#include <sstream>

#pragma comment(lib, "shell32.lib")

class SelectDirectoryMenu
{
private:
	std::wstring currentDirectory;

	std::wstring BrowseFolder(std::wstring saved_path);
public:

	SelectDirectoryMenu();

	void processMenu();

	std::string getCurrentDirectory();

	static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

};
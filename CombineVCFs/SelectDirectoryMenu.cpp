#include "SelectDirectoryMenu.h"

SelectDirectoryMenu::SelectDirectoryMenu()
{
	/*LPWSTR my_documents = L"";
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);
	// ERROR in executing SHGetFolderPath
	if (result != S_OK)
		std::cout << "Error: " << result << "\n";
	else
		currentDirectory = my_documents;*/
	m_wsCurrentDirectory = L"C:\\"; 
}

int CALLBACK SelectDirectoryMenu::BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{

	if (uMsg == BFFM_INITIALIZED)
	{
		std::string tmp = (const char *)lpData;
		std::cout << "path: " << tmp << std::endl;
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
	}

	return 0;
}

std::wstring SelectDirectoryMenu::BrowseFolder(std::wstring saved_path)
{
	TCHAR path[MAX_PATH];

	std::wstring wsaved_path(saved_path.begin(), saved_path.end());
	const wchar_t * path_param = wsaved_path.c_str();

	BROWSEINFO bi = { 0 };
	//bi.lpszTitle = ("Browse for folder...");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = (LPARAM)path_param;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != 0)
	{
		//get the name of the folder and put it in path
		SHGetPathFromIDList(pidl, path);

		//free memory used
		IMalloc * imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}

		return path;
	}

	return nullptr;
}

std::string SelectDirectoryMenu::getCurrentDirectory()
{
	return std::string(m_wsCurrentDirectory.begin(), m_wsCurrentDirectory.end());
}

std::wstring SelectDirectoryMenu::wGetCurrentDirectory()
{
	return m_wsCurrentDirectory;
}

void SelectDirectoryMenu::processMenu()
{
	m_wsCurrentDirectory = BrowseFolder(m_wsCurrentDirectory);
}
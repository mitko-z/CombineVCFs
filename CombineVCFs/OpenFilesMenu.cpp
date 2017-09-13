#include "OpenFilesMenu.h"

void OpenFilesMenu::openFilesDialog()
{
	OPENFILENAME ofn;

	WCHAR szFileName[MAX_PATH] = L"";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"VCF Files (*.vcf)\0*.vcf\0Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT;
	ofn.lpstrDefExt = L"vcf";

	GetOpenFileNameW(&ofn);

	wchar_t* str = ofn.lpstrFile;
	
	std::vector<std::wstring> selectedFiles;
	selectedFiles.push_back(str);
	str += (selectedFiles[0].length() + 1);
	int counter = 0;
	
	std::wstring fileName;
	std::wstring directory;
	while (*str) 
	{
		fileName = str;
		if (counter == 0)
		{
			directory = selectedFiles[0];
			selectedFiles[0] += L"\\";
			selectedFiles[0] += fileName;
		}
		else
		{
			selectedFiles.push_back(directory);
			selectedFiles[counter] += L"\\";
			selectedFiles[counter] += fileName;
		}
		str += (fileName.length() + 1);
		counter++;
	}
	/*for each(std::wstring file in selectedFiles)
	{
		std::wcout << file << std::endl;
	}

	pressAnyKey();*/
	pushToFields(selectedFiles);
}

void OpenFilesMenu::processMenu()
{
	openFilesDialog();
}

void OpenFilesMenu::pushToFields(std::vector<std::wstring> filesToPush)
{
	for each (std::wstring file in filesToPush)
	{
		bool isSelectedBefore = false;
		for each(std::wstring m_file in m_vwsFiles)
		{
			if (file == m_file)
			{
				isSelectedBefore = true;
				break;
			}
		}
		if (!isSelectedBefore)
		{
			m_vwsFiles.push_back(file);
			if (m_wsFilesAsString == NONE_SELECTED_TEXT)
			{
				m_wsFilesAsString = file;
			}
			else
			{
				m_wsFilesAsString += L" ";
				m_wsFilesAsString += file;
			}
		}
	}
}

void OpenFilesMenu::eraseFiles()
{
	m_wsFilesAsString = NONE_SELECTED_TEXT;
	m_vwsFiles.clear();
}
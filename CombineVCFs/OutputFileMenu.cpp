#include "OutputFileMenu.h"

std::wstring OutputFileMenu::saveFileDialog()
{
	OPENFILENAME ofn;

	WCHAR szFileName[MAX_PATH] = L"";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"txt";

	GetSaveFileName(&ofn);

	return ofn.lpstrFile;
}

void OutputFileMenu::processMenu()
{
	m_wsFileName = saveFileDialog();
}

std::string OutputFileMenu::getCurrentFileName()
{
	return std::string(m_wsFileName.begin(), m_wsFileName.end());
}

std::wstring OutputFileMenu::wGetCurrentFileName()
{
	return m_wsFileName;
}
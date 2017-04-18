#pragma once
#include "BaseMenu.h"
//#include "SelectDirectoryMenu.h"
//#include "RangeMenu.h"
#include "OpenFilesMenu.h"
#include "OutputFileMenu.h"
#include "ProcessVCFs.h"
#include <string> // +operator overload


class StartMenu : public BaseMenu
{
public:
	StartMenu() : BaseMenu("") {}
	void processMenu();

private:
	const std::string NOT_AVAIL_TEXT = "(UNDER CONSTRUCTION. Please be patient!)";
};
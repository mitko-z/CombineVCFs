#pragma once
#include "BaseMenu.h"
#include "SelectDirectoryMenu.h"
#include "RangeMenu.h"
#include "OutputFileMenu.h"
#include "ProcessVCFs.h"
#include <string> // +operator overload


class StartMenu :BaseMenu
{
public:
	StartMenu() : BaseMenu
		("Enter your choice:\n1. Select directory;\n2. Select range;\n3. Select output file name;\n4. PROCESS!\n0. Exit")
	{}

	void processMenu();
private:
	const std::string NOT_AVAIL_TEXT = "(UNDER CONSTRUCTION. Please be patient!)";
};
#include "RangeMenu.h"

std::string RangeMenu::getRange()
{
	std::string range = m_iLowerRange + " : " + m_iUpperRange;
	return range;
}

void RangeMenu::processMenu()
{
	while (1)
	{
		m_sMenuText = std::string("Enter range of which files to be processed!") + NEW_LINE +
			"Format: " + NEW_LINE +
			"N1 : N2 " + NEW_LINE +
			"where N1 is the number of the file with which to begin, " + NEW_LINE +
			"N2 is the number of the file with which to end." + NEW_LINE +
			"Note that the files in the current folder must be in format XXXX.vcf." + NEW_LINE +
			"If not - rename before proceeding else will not be able to process!" + NEW_LINE +
			NEW_LINE +
			"Type nothing if you want to cancel this entrance!";
		printText();

		std::string userInput = "";
		std::getline(std::cin, userInput);
		
		if (userInput == "")
			return;

		std::stringstream stream(userInput);
		int a(-1), b(-1);
		char colon;
		stream >> a;
		stream >> colon;
		stream >> b;

		if (a > 0 && b > 0 && a < b)
		{
			m_iLowerRange = a;
			m_iUpperRange = b;
			return; // berak;
		}
		else
		{
			std::cout << "Invalid input! Try again! Format expected N1 : N2" << std::endl;
			pressAnyKey();
		}
	}
}
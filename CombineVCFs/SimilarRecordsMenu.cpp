#include "SimilarRecordsMenu.h"

void SimilarRecordsMenu::processMenu()
{

	int choice = 0;

	
	m_sMenuText =
		"Those records below have similar fields. Choose what to do: " + NEW_LINE +
		"(1) Add both records;" + NEW_LINE +
		"(2) Merge (add data which is different)" + NEW_LINE +
		"(3) Replace the old record with the new one" + NEW_LINE +
		"(4) Skip the newer record" + NEW_LINE +
		"(0 or anything else) Cancel the whole operation" + NEW_LINE;
	printText();
	std::cout << "Old record: " << NEW_LINE;
	m_vcfOldRecord.print();
	std::cout << NEW_LINE << "New record: " << NEW_LINE;
	m_vcfNewRecord.print();

	choice = getChoice(4);

	if (choice == 0)
		exit(0);

	actionTaken = static_cast<actionType>(choice - 1);
	
}
#pragma once

#include "BaseMenu.h"
#include "VCFRecord.h"

class SimilarRecordsMenu : public BaseMenu
{
private:
	SimilarRecordsMenu() {}

	VCFRecord m_vcfOldRecord;
	VCFRecord m_vcfNewRecord;
public:

	SimilarRecordsMenu(VCFRecord oldRecord, VCFRecord newRecord) : 
		m_vcfOldRecord(oldRecord), m_vcfNewRecord(newRecord) 
	{ }

	enum actionType
	{
		to_continue,
		merge,
		replace,
		skip,
	};
	actionType actionTaken;
	
	void processMenu();
};
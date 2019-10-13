#pragma once

#include "BaseVCFField.h"
#include <sstream>


class ListOfVCFFields : public BaseVCFField
{
private:
public:
	//typedef std::vector<std::pair<std::wstring, std::wstring>> VectPairWstrings;
	typedef std::map<std::wstring, std::wstring> UMapWstrings;
	UMapWstrings dataFields;

	ListOfVCFFields(std::wstring fieldName, UMapWstrings dataFields) :
		BaseVCFField(fieldName),
		dataFields(dataFields)
	{ }

	std::wostream& print(std::wostream& out) const override;

	void insertData(std::wstring value, std::wstring type);

	bool isEqualTo(std::wstring ListOfWstringsAsWstring);

	bool isSimilarTo(std::wstring fieldsAsWstringToCompareWith);

	std::wstring getData();

	std::wstring getFormatedData();

	void addDataIfDontExist(std::wstring fieldToAddFrom);

private:
	//typedef std::vector<std::pair<std::wstring, std::wstring>> VectPairWstrings;
	UMapWstrings convertToUMapWstrings(std::wstring formatedWstring);

	bool areUMapsSimilar(UMapWstrings vector1, UMapWstrings vector2);

};
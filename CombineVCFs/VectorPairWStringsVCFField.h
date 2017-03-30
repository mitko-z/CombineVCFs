#pragma once

#include "BaseVCFField.h"
#include <sstream>


class VectorPairWStringsVCFField : public BaseVCFField
{
private:
public:
	typedef std::vector<std::pair<std::wstring, std::wstring>> VectPairWstrings;
	VectPairWstrings dataFields;

	VectorPairWStringsVCFField(std::wstring fieldName, VectPairWstrings dataFields) :
		BaseVCFField(fieldName),
		dataFields(dataFields)
	{ }

	std::wostream& print(std::wostream& out) const override;

	void insertData(std::wstring value, std::wstring type);

	bool isEqualTo(std::wstring vectPairWstringsAsWstring);

	bool isSimilarTo(std::wstring fieldsAsWstringToCompareWith);

	std::wstring getData();

	std::wstring getFormatedData();

	void addDataIfDontExist(std::wstring fieldToAddFrom);

private:
	typedef std::vector<std::pair<std::wstring, std::wstring>> VectPairWstrings;
	VectPairWstrings convertToVectPairWstrings(std::wstring formatedWstring);

	bool areVectorsSimilar(VectPairWstrings  vector1, VectPairWstrings vector2);

};
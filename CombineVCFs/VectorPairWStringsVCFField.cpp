#include "VectorPairWStringsVCFField.h"

std::wostream& VectorPairWStringsVCFField::print(std::wostream& out) const
{
	if (!dataFields.empty())
	{
		out << nameField << L"(s): " << std::endl;
		for each(auto record in dataFields)
		{
			out << record.first << L" - " << record.second << std::endl;
		}
	}
	return out;
}

void VectorPairWStringsVCFField::insertData(std::wstring value, std::wstring type)
{
	this->dataFields.push_back(make_pair(type, value));
}

bool VectorPairWStringsVCFField::isEqualTo
								(
									std::wstring vectPairWstringsAsWstring
								)
{
	if (vectPairWstringsAsWstring != L"")
	{
		VectPairWstrings vectToCompareWith = convertToVectPairWstrings(vectPairWstringsAsWstring);

		if (this->dataFields.size() != vectToCompareWith.size())
		{
			return false;
		}
		else
		{
			for (int i = 0; i < this->dataFields.size(); i++)
			{
				if
					(
						this->dataFields[i].first != vectToCompareWith[i].first ||
						this->dataFields[i].second != vectToCompareWith[i].second
						)
					return false;
			}
		}
	}
	else
	{
		return (this->dataFields.size() == 0); 
		// return true if both vectPairWstringsAsWstring and the size of dataFields are empty
		// otherwise return false as current vector is not empty but vectPairWstringsAsWstring is
	}
}

bool VectorPairWStringsVCFField::areVectorsSimilar
								(
									VectPairWstrings vector1,
									VectPairWstrings vector2
								)
{

	if (vector1.size() == 0)
		return false;

	for each (auto pair1 in vector1)
	{
		for each (auto pair2 in vector2)
		{
			if (pair1.second == pair2.second)
				return true;
		}
	}

	return false;
}

std::wstring VectorPairWStringsVCFField::getData()
{
	std::wstring outputWstring;
	for each (auto field in this->dataFields)
	{
		outputWstring += field.first;
		outputWstring += L"\n";
		outputWstring += field.second;
		outputWstring += L"\n";
	}
	return outputWstring;
}

std::wstring VectorPairWStringsVCFField::getFormatedData()
{
	//fieldsName << L";TYPE=" << field.first << ":" << field.second
	std::wstring outputWstring;
	for each(auto field in this->dataFields)
	{
		outputWstring += this->nameField;
		outputWstring += L";TYPE=";
		outputWstring += field.first;
		outputWstring += L":";
		outputWstring += field.second;
		outputWstring += L"\n";
	}
	return outputWstring;
}

std::vector<std::pair<std::wstring, std::wstring>> VectorPairWStringsVCFField::convertToVectPairWstrings(std::wstring formatedWstring)
{
	std::wstringstream ss(formatedWstring);
	std::wstring firstLine;
	std::wstring secondLine;

	VectPairWstrings outputVect;
	std::getline(ss, firstLine);
	while (std::getline(ss, secondLine))
	{
		outputVect.push_back(std::make_pair(firstLine, secondLine));
		std::getline(ss, firstLine);
	}

	return outputVect;
}

bool VectorPairWStringsVCFField::isSimilarTo(std::wstring fieldsAsWstringToCompareWith)
{
	VectPairWstrings vectToCompareWith = convertToVectPairWstrings(fieldsAsWstringToCompareWith);
	return areVectorsSimilar(this->dataFields, vectToCompareWith);
}

void VectorPairWStringsVCFField::addDataIfDontExist(std::wstring fieldToAddFrom)
{
	VectPairWstrings vectorToAddFrom = convertToVectPairWstrings(fieldToAddFrom);

	for each(auto newField in vectorToAddFrom)
	{
		bool toAddNewData = true;
		for each(auto thisField in this->dataFields)
		{
			if (newField.second == thisField.second)
			{
				toAddNewData = false;
				break;
			}

		}
		if (toAddNewData)
		{
			this->dataFields.push_back(newField);
		}
	}
}
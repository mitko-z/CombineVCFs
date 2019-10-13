#include "ListOfVCFFields.h"

std::wostream& ListOfVCFFields::print(std::wostream& out) const
{
	if (!dataFields.empty())
	{
		out << getName() << L"(s): " << std::endl;
		for each(auto record in dataFields)
		{
			out << record.first << L" - " << record.second << std::endl;
		}
	}
	return out;
}

void ListOfVCFFields::insertData(std::wstring value, std::wstring type)
{
	this->dataFields[type] = value;
}

bool ListOfVCFFields::isEqualTo
								(
									std::wstring ListOfWstringsAsWstring
								)
{
	if (ListOfWstringsAsWstring != L"")
	{
		UMapWstrings UMapToCompareWith = convertToUMapWstrings(ListOfWstringsAsWstring);

		if (this->dataFields.size() != UMapToCompareWith.size())
		{
			return false;
		}
		else
		{
			//for (int i = 0; i < this->dataFields.size(); i++)
			for
				(
					std::map<std::wstring, std::wstring>::iterator 
						it1 = this->dataFields.begin(),
						it2 = UMapToCompareWith.begin();
					it1 != dataFields.end();
					it1++, it2++
				)
			{
				/*if
					(
						this->dataFields[i].first != UMapToCompareWith[i].first ||
						this->dataFields[i].second != UMapToCompareWith[i].second
						)*/
				if ((it1->first != it2->first) || (it1->second != it2->second))
				{
					return false;
				}
			}
		}
	}
	else
	{
		return (this->dataFields.size() == 0); 
		// return true if both ListOfWstringsAsWstring and the size of dataFields are empty
		// otherwise return false as current map is not empty but ListOfWstringsAsWstring is
	}
}

bool ListOfVCFFields::areUMapsSimilar
								(
									UMapWstrings uMap1,
									UMapWstrings uMap2
								)
{

	if (uMap1.size() == 0)
		return false;

	for each (auto pair1 in uMap1)
	{
		for each (auto pair2 in uMap2)
		{
			if (pair1.second == pair2.second)
				return true;
		}
	}

	return false;
}

std::wstring ListOfVCFFields::getData()
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

std::wstring ListOfVCFFields::getFormatedData()
{
	//fieldsName << L";TYPE=" << field.first << ":" << field.second
	std::wstring outputWstring;
	for each(auto field in this->dataFields)
	{
		outputWstring += this->getName();
		outputWstring += L";TYPE=";
		outputWstring += field.first;
		outputWstring += L":";
		outputWstring += field.second;
		outputWstring += L"\n";
	}
	return outputWstring;
}

std::map<std::wstring, std::wstring> ListOfVCFFields::convertToUMapWstrings(std::wstring formatedWstring)
{
	std::wstringstream ss(formatedWstring);
	std::wstring firstLine;
	std::wstring secondLine;

	UMapWstrings outputUMap;
	std::getline(ss, firstLine);
	while (std::getline(ss, secondLine))
	{
		outputUMap[firstLine] = secondLine;
		std::getline(ss, firstLine);
	}

	return outputUMap;
}

bool ListOfVCFFields::isSimilarTo(std::wstring fieldsAsWstringToCompareWith)
{
	UMapWstrings uMapToCompareWith = convertToUMapWstrings(fieldsAsWstringToCompareWith);
	return areUMapsSimilar(this->dataFields, uMapToCompareWith);
}

void ListOfVCFFields::addDataIfDontExist(std::wstring fieldToAddFrom)
{
	UMapWstrings uMapToAddFrom = convertToUMapWstrings(fieldToAddFrom);

	for each(auto newField in uMapToAddFrom)
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
			this->dataFields.insert(newField);
		}
	}
}
#pragma once

#include <locale> // std::wstring
#include <iostream> // std::wcout
#include <vector> // std::vector
#include <utility> // std::pair
#include <map>


class BaseVCFField
{
protected:
	BaseVCFField(std::wstring nameField) :nameField(nameField) {}

public:
	std::wstring getName() const { return nameField; }

	friend std::wostream& operator<<(std::wostream &out, const BaseVCFField &b)
	{ 
		return b.print(out);
	}

	// pure virtuals
	virtual std::wostream& print(std::wostream& out) const = 0;
	virtual void insertData(std::wstring value, std::wstring type) = 0;
	virtual bool isEqualTo(std::wstring fieldToCompare) = 0;
	virtual bool isSimilarTo(std::wstring fieldToCompare) = 0;
	virtual std::wstring getData() = 0;
	virtual std::wstring getFormatedData() = 0;
	virtual void addDataIfDontExist(std::wstring fieldToAddFrom) = 0;

private:
	std::wstring nameField;
};

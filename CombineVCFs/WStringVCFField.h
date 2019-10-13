#pragma once

#include "BaseVCFField.h"


class WStringVCFField : public BaseVCFField
{
public:
	std::wstring data;
	WStringVCFField(std::wstring name, std::wstring data) :BaseVCFField(name), data(data) {}

	std::wostream& print(std::wostream& out) const override;

	void insertData(std::wstring value, std::wstring type);

	bool isEqualTo(std::wstring data);

	bool isSimilarTo(std::wstring data) { return isEqualTo(data); }

	std::wstring getData() { return data; }

	std::wstring getFormatedData() { return this->getName() + L":" + data + L"\n"; }

	void addDataIfDontExist(std::wstring fieldToAddFrom);

};
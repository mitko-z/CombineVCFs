#include "WStringVCFField.h"

std::wostream& WStringVCFField::print(std::wostream& out) const
{
	if (this->data!=L"")
	{
		out << nameField << L"(s): " << std::endl;
		out << this->data << std::endl;
	}
	return out;
}

void WStringVCFField::insertData(std::wstring value, std::wstring type)
{
	this->data = value;
}

bool WStringVCFField::isEqualTo(std::wstring data)
{
	return this->data == data;
}

void WStringVCFField::addDataIfDontExist(std::wstring fieldToAddFrom)
{
	if (this->data == L"" && fieldToAddFrom != L"")
	{
		this->data = fieldToAddFrom;
	}
}
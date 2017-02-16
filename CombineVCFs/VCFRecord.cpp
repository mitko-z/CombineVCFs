#include "VCFRecord.h"

VCFRecord::VCFRecord()
{

}

void VCFRecord::insertData(string fieldCriteria, string value, string type = "")
{
	if (fieldCriteria == "N:")
	{
		n = value;
		return;
	}
	if (fieldCriteria == "FN:")
	{
		fn = value;
		return;
	}
	if (fieldCriteria == "NOTE:")
	{
		note = value;
		return;
	}
	if (fieldCriteria == "URL:")
	{
		url = value;
		return;
	}
	if (fieldCriteria == "TITLE:")
	{
		title = value;
		return;
	}
	if (fieldCriteria == "X-SKYPE-USERNAME:")
	{
		xSkypeUsername = value;
		return;
	}
	if (fieldCriteria == "BDAY:")
	{
		bday = value;
		return;
	}
	if (fieldCriteria == "TEL;")
	{
		int intValue = stoi(value);
		phones.push_back(make_pair(type, intValue));
		return;
	}
	if (fieldCriteria == "EMAIL;")
	{
		emails.push_back(make_pair(type, value));
		return;
	}
	if (fieldCriteria == "ADR;")
	{
		adresses.push_back(make_pair(type, value));
		return;
	}
}
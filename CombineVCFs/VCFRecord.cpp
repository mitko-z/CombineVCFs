#include "VCFRecord.h"

VCFRecord::VCFRecord()
{

}

void VCFRecord::insertData(wstring fieldCriteria, wstring value, wstring type)
{
	if (fieldCriteria == L"N")
	{
		n = value;
		return;
	}
	if (fieldCriteria == L"FN")
	{
		fn = value;
		return;
	}
	if (fieldCriteria == L"NOTE")
	{
		note = value;
		return;
	}
	if (fieldCriteria == L"URL")
	{
		url = value;
		return;
	}
	if (fieldCriteria == L"TITLE")
	{
		title = value;
		return;
	}
	if (fieldCriteria == L"X-SKYPE-USERNAME")
	{
		xSkypeUsername = value;
		return;
	}
	if (fieldCriteria == L"BDAY")
	{
		bday = value;
		return;
	}
	if (fieldCriteria == L"TEL")
	{
		phones.push_back(make_pair(type, value));
		return;
	}
	if (fieldCriteria == L"EMAIL")
	{
		emails.push_back(make_pair(type, value));
		return;
	}
	if (fieldCriteria == L"ADR")
	{
		addresses.push_back(make_pair(type, value));
		return;
	}
	return;
}

void VCFRecord::print()
{
	
	
	printField(L"Title", title);
	printField(L"Name", n);
	printField(L"Family Name", fn);
	printField(L"Phone", phones);
	printField(L"E-mail", emails);
	printField(L"Skype", xSkypeUsername);
	printField(L"Address", addresses);
	printField(L"Organization", org);
	printField(L"Note(s)", note);
	printField(L"Website", url);
	printField(L"Birth Day", bday);
	
}

void VCFRecord::printField(std::wstring phrase, std::wstring field)
{
	if (field != L"")
		wcout << phrase << L": " << field << endl;
}

void VCFRecord::printField(std::wstring phrase, vector<pair<wstring, int>> field)
{
	if (!field.empty())
	{
		wcout << phrase << L"(s): " << endl;
		for each(auto record in field) // the same as for(auto record : field)
		{
			wcout << record.first << L" - " << to_wstring(record.second) << endl;
		}
	}
}

void VCFRecord::printField(std::wstring phrase, vector<pair<wstring, wstring>> field)
{
	if (!field.empty())
	{
		wcout << phrase << L"(s): " << endl;
		for each(auto record in field) 
		{
			wcout << record.first << L" - " << record.second << endl;
		}
	}
}

bool VCFRecord::operator==(VCFRecord recordToCompareWith)
{
	
	if (this->fn != recordToCompareWith.fn)
		return false;
	if (this->note != recordToCompareWith.note)
		return false;
	if (this->url != recordToCompareWith.url)
		return false;
	if (this->org != recordToCompareWith.org)
		return false;
	if (this->title != recordToCompareWith.title)
		return false;
	if (this->xSkypeUsername != recordToCompareWith.xSkypeUsername)
		return false;
	if (this->bday != recordToCompareWith.bday)
		return false;
	if (this->phones.size() != recordToCompareWith.phones.size())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < this->phones.size(); i++)
		{
			if 
				(
					this->phones[i].first != recordToCompareWith.phones[i].first || 
					this->phones[i].second != recordToCompareWith.phones[i].second
				)
				return false;
		}
	}
	if (this->emails.size() != recordToCompareWith.emails.size())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < this->emails.size(); i++)
		{
			if
				(
					this->emails[i].first != recordToCompareWith.emails[i].first ||
					this->emails[i].second != recordToCompareWith.emails[i].second
					)
				return false;
		}
	}
	if (this->addresses.size() != recordToCompareWith.addresses.size())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < this->addresses.size(); i++)
		{
			if
				(
					this->addresses[i].first != recordToCompareWith.addresses[i].first ||
					this->addresses[i].second != recordToCompareWith.addresses[i].second
					)
				return false;
		}
	}

	return true;
}
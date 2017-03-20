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
	//printField(L"Name", n);    // <-- this field has the same data as fn - no need to print
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
	if (!areVectorsEqual(this->phones, recordToCompareWith.phones))
		return false;
	if (!areVectorsEqual(this->emails, recordToCompareWith.emails))
		return false;
	if (!areVectorsEqual(this->addresses, recordToCompareWith.addresses))
		return false;
	

	return true;
}

bool VCFRecord::areVectorsEqual
		(
			vector<pair<wstring, wstring>> vector1, 
			vector<pair<wstring, wstring>> vector2
		)
{
	if (vector1.size() != vector2.size())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < vector1.size(); i++)
		{
			if
				(
					vector1[i].first != vector2[i].first ||
					vector1[i].second != vector2[i].second
				)
				return false;
		}
	}
}

bool VCFRecord::isSimilarTo(VCFRecord recordToCompareWith)
{
	if (this->fn != L"" && this->fn == recordToCompareWith.fn)
		return true;
	if (this->note != L"" && this->note == recordToCompareWith.note)
		return true;
	if (this->url != L"" && this->url == recordToCompareWith.url)
		return true;
	if (this->org != L"" && this->org == recordToCompareWith.org)
		return true;
	if (this->title != L"" && this->title == recordToCompareWith.title)
		return true;
	if (this->xSkypeUsername != L"" && this->xSkypeUsername == recordToCompareWith.xSkypeUsername)
		return true;
	if (this->bday != L"" && this->bday == recordToCompareWith.bday)
		return true;
	if (areVectorsSimilar(this->phones, recordToCompareWith.phones))
		return true;
	if (areVectorsSimilar(this->emails, recordToCompareWith.emails))
		return true;
	if (areVectorsSimilar(this->addresses, recordToCompareWith.addresses))
		return true;

	return false;
}

bool VCFRecord::areVectorsSimilar
				(
					vector<pair<wstring, wstring>> vector1,
					vector<pair<wstring, wstring>> vector2
				)
{
	
	if (vector1.size() == 0)
		return false;

	for each (pair<wstring, wstring> pair1 in vector1)
	{
		for each (pair<wstring, wstring> pair2 in vector2)
		{
			if (pair1.second == pair2.second)
				return true;
		}
	}
	
	return false;
}

void VCFRecord::mergeData(VCFRecord recordToAdd)
{
	addDataIfDontExist(this->n, recordToAdd.n);
	addDataIfDontExist(this->fn, recordToAdd.fn);
	addDataIfDontExist(this->bday, recordToAdd.bday);
	addDataIfDontExist(this->note, recordToAdd.note);
	addDataIfDontExist(this->org, recordToAdd.org);
	addDataIfDontExist(this->title, recordToAdd.title);
	addDataIfDontExist(this->url, recordToAdd.url);
	addDataIfDontExist(this->addresses, recordToAdd.addresses);
	addDataIfDontExist(this->emails, recordToAdd.emails);
	addDataIfDontExist(this->phones, recordToAdd.phones);
	addDataIfDontExist(this->xSkypeUsername, recordToAdd.xSkypeUsername);
}

void VCFRecord::addDataIfDontExist(std::wstring &field, std::wstring dataToAdd)
{
	if (field == L"" && dataToAdd != L"")
	{
		field = dataToAdd;
	}
}

void VCFRecord::addDataIfDontExist
				(
					vector<pair<wstring, wstring>> &vectorField, 
					vector<pair<wstring, wstring>> vectorToAddFrom
				)
{
	
	for each(auto newField in vectorToAddFrom)
	{
		bool toAddNewData = true;
		for each(auto thisField in vectorField)
		{
			if (newField.second == thisField.second)
			{
				toAddNewData = false;
				break;
			}

		}
		if (toAddNewData)
		{
			vectorField.push_back(newField);
		}
	}

}
#include "VCFRecord.h"

VCFRecord::VCFRecord() 
{
	// add existing types of records in a VCFRecord
	//fields.push_back(new WStringVCFField(L"N", L""));
	fields.push_back(new WStringVCFField(L"FN", L""));
	fields.push_back(new WStringVCFField(L"NOTE", L""));
	fields.push_back(new WStringVCFField(L"URL", L""));
	fields.push_back(new WStringVCFField(L"groupedLogs1.URL", L""));
	fields.push_back(new WStringVCFField(L"ORG", L""));
	fields.push_back(new WStringVCFField(L"TITLE", L""));
	fields.push_back(new WStringVCFField(L"X-SKYPE-USERNAME", L""));
	fields.push_back(new WStringVCFField(L"X-SKYPE-USERNAME", L""));
	fields.push_back(new WStringVCFField(L"BDAY", L""));
	
	std::map<std::wstring, std::wstring> aMap;
	//ListOfVCFFields vectFields = ListOfVCFFields(L"TEL", aVect);
	fields.push_back(new ListOfVCFFields(L"TEL", aMap));
	//vectFields = ListOfVCFFields(L"EMAIL", aVect);
	fields.push_back(new ListOfVCFFields(L"EMAIL", aMap));
	//vectFields = ListOfVCFFields(L"ADR", aVect);
	fields.push_back(new ListOfVCFFields(L"ADR", aMap));
	fields.push_back(new ListOfVCFFields(L"groupedLogs1.ADR", aMap));


	/* wstring n;
	wstring fn;
	wstring note;
	wstring url;
	wstring org;
	wstring title;
	wstring xSkypeUsername;
	wstring bday;
	vector<pair<wstring, wstring>> phones; // the type of phone, the phone number
	vector<pair<wstring, wstring>> emails; // type of e-mail, the e-mail
	vector<pair<wstring, wstring>> addresses; // type of address, the address */
}

//VCFRecord::~VCFRecord()
//{
//	for (int i = 0; i < this->fields.size(); i++)
//	{
//		//delete fields[i];
//	}
//}

void VCFRecord::insertData(wstring fieldCriteria, wstring value, wstring type)
{
	unifyData(fieldCriteria, value, type);
	for (int i = 0; i < this->fields.size(); i++)
	{
		if ( (*fields[i]).getName() == fieldCriteria)
		{
			(*fields[i]).insertData(value, type);
			return;
		}
	}

	/*if (fieldCriteria == L"N")
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
	}*/
	return;
}

void VCFRecord::unifyData(wstring &fieldCriteria, wstring &value, wstring &type)
{
	if (type == L"Work") type = L"WORK";
	if (type == L"Home") type = L"HOME";
	if (type == L"Mobile") type = L"CELL";
	if (fieldCriteria == L"TEL")
	{
		if (value.size() >= 4)
		{
			if (wstring(value.begin(), value.begin() + 4) == L"+359")
			{
				wstring newVal = L"0" + wstring(value.begin() + 5, value.end());
				value = newVal;
			}
		}
		value.erase(std::remove(value.begin(), value.end(), L'-'), value.end());
		value.erase(std::remove(value.begin(), value.end(), L' '), value.end());
		/*for (int i = value.size() - 1; i >= 0; --i)
		{
			if (value[i] == L'-')
			{
				value.erase(i, 1);
			}
		}*/
	}
}

std::wstring VCFRecord::wName()
{
	std::wstring n = L"";
	for (auto field : this->fields)
	{
		if (field->getName() == L"FN")
		{
			n = field->getData();
			break;
		}
	}
	return n;
}

void VCFRecord::print()
{

	for (int i = 0; i < this->fields.size(); i++)
	{
		if ((*fields[i]).getName() != L"N")	// <-- this field has the same data as fn => no need to print
		{
			std::wcout << (*fields[i]); // TODO: make this print in separate class which prints trough different methods
		}
	}

	//printField(L"Title", title);
	////printField(L"Name", n);    
	//printField(L"Family Name", fn);
	//printField(L"Phone", phones);
	//printField(L"E-mail", emails);
	//printField(L"Skype", xSkypeUsername);
	//printField(L"Address", addresses);
	//printField(L"Organization", org);
	//printField(L"Note(s)", note);
	//printField(L"Website", url);
	//printField(L"Birth Day", bday);
}

//void VCFRecord::printField(std::wstring phrase, std::wstring field)
//{
//	if (field != L"")
//		wcout << phrase << L": " << field << endl;
//}
//
//void VCFRecord::printField(std::wstring phrase, vector<pair<wstring, wstring>> field)
//{
//	if (!field.empty())
//	{
//		wcout << phrase << L"(s): " << endl;
//		for each(auto record in field) 
//		{
//			wcout << record.first << L" - " << record.second << endl;
//		}
//	}
//}

bool VCFRecord::operator==(VCFRecord recordToCompareWith)
{
	for (int i = 0; i < this->fields.size(); i++)
	{
		if (!(*fields[i]).isEqualTo((*recordToCompareWith.fields[i]).getData()))
		{
			return false;
		}
	}

	/*if (this->fn != recordToCompareWith.fn)
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
		return false;*/

	return true;
}



bool VCFRecord::isSimilarTo(VCFRecord recordToCompareWith)
{
	for (int i = 0; i < this->fields.size(); i++)
	{
		if
			(
				(*fields[i]).getData() != L"" &&
				(*fields[i]).isSimilarTo((*recordToCompareWith.fields[i]).getData())
			)
		{
			return true;
		}
	}

	/*if (this->fn != L"" && this->fn == recordToCompareWith.fn)
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
	if (areUMapsSimilar(this->phones, recordToCompareWith.phones))
		return true;
	if (areUMapsSimilar(this->emails, recordToCompareWith.emails))
		return true;
	if (areUMapsSimilar(this->addresses, recordToCompareWith.addresses))
		return true;*/

	return false;
}



void VCFRecord::mergeData(VCFRecord recordToAdd)
{
	for (int i = 0; i < this->fields.size(); i++)
	{
		std::wstring data = (*recordToAdd.fields[i]).getData();
		(*fields[i]).addDataIfDontExist((*recordToAdd.fields[i]).getData());
	}
	/*addDataIfDontExist(this->n, recordToAdd.n);
	addDataIfDontExist(this->fn, recordToAdd.fn);
	addDataIfDontExist(this->bday, recordToAdd.bday);
	addDataIfDontExist(this->note, recordToAdd.note);
	addDataIfDontExist(this->org, recordToAdd.org);
	addDataIfDontExist(this->title, recordToAdd.title);
	addDataIfDontExist(this->url, recordToAdd.url);
	addDataIfDontExist(this->addresses, recordToAdd.addresses);
	addDataIfDontExist(this->emails, recordToAdd.emails);
	addDataIfDontExist(this->phones, recordToAdd.phones);
	addDataIfDontExist(this->xSkypeUsername, recordToAdd.xSkypeUsername);*/
}

//void VCFRecord::addDataIfDontExist(std::wstring *field, std::wstring dataToAdd)
//{
//	if (field == L"" && dataToAdd != L"")
//	{
//		field = dataToAdd;
//	}
//}

//void VCFRecord::addDataIfDontExist
//				(
//					vector<pair<wstring, wstring>> &vectorField, 
//					vector<pair<wstring, wstring>> vectorToAddFrom
//				)
//{
//	
//	for each(auto newField in vectorToAddFrom)
//	{
//		bool toAddNewData = true;
//		for each(auto thisField in vectorField)
//		{
//			if (newField.second == thisField.second)
//			{
//				toAddNewData = false;
//				break;
//			}
//
//		}
//		if (toAddNewData)
//		{
//			vectorField.push_back(newField);
//		}
//	}
//
//}
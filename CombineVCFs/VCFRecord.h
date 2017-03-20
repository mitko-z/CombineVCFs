#pragma once
#include <string>
#include <map> // map<T1,Y2>
#include <utility> // pair<T1, T2>
#include <vector> // vector<T>
#include <locale> // unicode chars and strings
#include <iostream> // cout
#include <algorithm> // std::find for operator== overload

using namespace std;

struct VCFRecord
{
public:
	//fields
	wstring n;
	wstring fn;
	wstring note;
	wstring url;
	wstring org;
	wstring title;
	wstring xSkypeUsername;
	wstring bday;
	vector<pair<wstring, wstring>> phones; // the type of phone, the phone number
	vector<pair<wstring, wstring>> emails; // type of e-mail, the e-mail
	vector<pair<wstring, wstring>> addresses; // type of address, the address

	// constructor
	VCFRecord();

	// insert the value (and type if necessary) into apropriate VCFRecord's field according fieldCriteria
	void insertData(wstring fieldCriteria, wstring value, wstring type = L"");

	void print();

	bool operator==(VCFRecord recordToCompareWith);

	bool isSimilarTo(VCFRecord recordToCompareWith);

	void mergeData(VCFRecord recordToAdd);

private:
	void printField(std::wstring phrase, wstring field);

	void printField(std::wstring phrase, vector<pair<wstring, int>> field);

	void printField(std::wstring phrase, vector<pair<wstring, wstring>> field);

	bool areVectorsEqual(vector<pair<wstring, wstring>> vector1, vector<pair<wstring, wstring>> vector2);

	bool areVectorsSimilar(vector<pair<wstring, wstring>> vector1, vector<pair<wstring, wstring>> vector2);

	void addDataIfDontExist(std::wstring &field, std::wstring dataToAdd);

	void addDataIfDontExist(vector<pair<wstring, wstring>> &vectorField, vector<pair<wstring, wstring>> vectorToAddFrom);
};


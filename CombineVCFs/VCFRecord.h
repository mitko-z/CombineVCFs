#pragma once
#include <string>
#include <map> // map<T1,Y2>
#include <utility> // pair<T1, T2>
#include <vector> // vector<T>

using namespace std;

struct VCFRecord
{
public:
	//fields
	string n;
	string fn;
	string note;
	string url;
	string org;
	string title;
	string xSkypeUsername;
	string bday;
	vector<pair<string, int>> phones; // string - the type of phone; int - the phone number
	vector<pair<string, string>> emails; // type of e-mail, the e-mail
	vector<pair<string, string>> adresses; // type of address, the address

	// constructor
	VCFRecord();

	// insert the value (and type if necessar) into apropriate VCFRecord's field according fieldCriteria
	void insertData(string fieldCriteria, string value, string type = "");
};


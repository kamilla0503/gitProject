#pragma once
#include<string>

using namespace std;
class labeltype {
public:
	char name;
	bool label_HN, label_CA, label_CO;
	labeltype(char lname = 'X', bool l_HN = 0, bool l_CA = 0, bool l_CO = 0);
	bool operator<(const labeltype & t2);
	bool operator==(const labeltype & t2);
};
bool operator<(const labeltype& t1, const labeltype& t2);
bool operator==(const labeltype& t1, const char& s2);
bool operator==(const char& s1, const labeltype& t2);
//bool operator==(labeltype& t1, const char& s2);
//bool operator==(labeltype& t1, const labeltype& t2);


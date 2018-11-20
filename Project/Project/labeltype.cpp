#include"labeltype.h"

bool labeltype::operator<(const labeltype& t2) {
	return (this->name < t2.name);
}

bool labeltype::operator==(const labeltype& t2) {
	return (this->name < t2.name);
}

bool operator<(const labeltype& t1, const labeltype& t2) {
	return (t1.name < t2.name);
}

bool operator==(const labeltype& t1, const char& s2) {
	return (t1.name == s2);
}

/**
bool operator==( labeltype& t1, const char& s2) {
	return (t1.name == s2);
}
**/


bool operator==(const char& s1, const labeltype& t2) {
	return (s1 == t2.name);
}

bool operator==(const labeltype& t1, const labeltype& t2) { 
	return (t1.name == t2.name);
}


/**
bool operator==( labeltype& t1, const labeltype& t2) {
	return (t1.name == t2.name);
}**/


labeltype::labeltype(char lname , bool l_HN , bool l_CA , bool l_CO ) {
	name = lname;
	label_HN = l_HN;
	label_CA = l_CA;
	label_CO = l_CO;
}
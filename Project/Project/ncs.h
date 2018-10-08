#pragma once
#ifndef NCS_H_INCLUDED
#define NCS_H_INCLUDED
#include<string>
#include<vector>
#include<map>
#include<set>
using namespace std;

class labeltype {
public:
	string name;
	int  isotopes;
	//bool HN, CA, CO;
	// 
	labeltype(string lname = "X", int  lisotopes = 0) {
		name = lname;
		isotopes = lisotopes;
	}

	bool operator<(const labeltype & t2);

};



bool operator<(const labeltype& t1, const labeltype& t2);
bool operator==(const labeltype& t1, const string& s2);
bool operator==(const string& s1, const labeltype& t2);


class spectrum {
public:
	string name;
	spectrum(string sname);
	int has_signal(labeltype label_type_1, labeltype label_type_2);
};

class NCS {
public:
	const vector <string> NITRO_TYPES = { "N", "D", "S", "T" };
	string name;
	vector<spectrum>spec_list;
	vector<labeltype> label_types;
	bool deuterated;
	map<string, labeltype> label_dict;
	vector <string> letters;
	//vector <> spectra_numbers; 
	map<labeltype, int> label_power;
	map <labeltype, map <labeltype, string>> codes_dict;
	vector <vector <int>> vectors;
	//map <labeltype, string> subdict;
	
	//name, spectra_list, label_types, deuterated = False)
	//NCS(string name_ncs, vector<spectrum>spectra_list_ncs, vector<labeltype> label_types_ncs, bool deuterated_ncs = false);
	NCS(string name_ncs = "", vector<spectrum>spectra_list_ncs = {}, vector<labeltype> label_types_ncs = {}, bool deuterated_ncs = 0);
	void make_coding_table(void); 
	NCS& operator=(NCS& other);
	string calc_code(string pattern_1, string pattern_2);

};



class Scheme {
public:
	string name;
	NCS ncs;
	int samples;
	vector <string> patterns;
	set <string> codes; 
	set <string> new_codes;
	map <string, int> simplified;
	bool good;
	Scheme(string sname, NCS sncs, int  bsamples, vector <string>  bpatterns); //patterns 
	bool check_codes();
	void simplify();
	bool check_patterns(vector <string> patterns);
	void sort();
	void add_new_codes(string new_pattern);
	void add_pattern(string new_pattern); 
	bool try_pattern(string  new_pattern);


};


//for scheme (patterns) 
bool pattern_bigger(string pattern1, string  pattern2);
string simplify_pattern(string pattern);

#endif  // NCS_H_INCLUDED
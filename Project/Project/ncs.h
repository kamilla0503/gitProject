#pragma once
#ifndef NCS_H_INCLUDED
#define NCS_H_INCLUDED
#include<map>
#include<set>
#include<fstream>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<regex>
#include<tuple>
#include<time.h> 
#include"Spectrum.h"
class NCS {
public:
	const vector <char> NITRO_TYPES = { 'N', 'D', 'S', 'T' };
	string name;
	vector<spectrum>spec_list;
	vector<labeltype> label_types;
	bool deuterated;
	map<char, labeltype> label_dict;
	vector <char> letters;
	map<labeltype, int> label_power;
	map <labeltype, map <labeltype, string>> codes_dict;
	vector <vector <int>> vectors;
	NCS(string name_ncs = "", vector<spectrum>spectra_list_ncs = {}, vector<labeltype> label_types_ncs = {}, bool deuterated_ncs = 0);
	void make_coding_table(void); 
	NCS& operator=(NCS& other);
	string calc_code(string pattern_1, string pattern_2);
	bool check_power(string new_pattern,int min_depth);
};


bool pattern_bigger(string pattern1, string  pattern2);
string simplify_pattern(string pattern);
map <string, int>  simplify_list_of_patterns(vector<string> list_of_patterns); 
tuple<int, int > count_type_in_list_of_simplified(map <string, int> simplified, int index_of_type); 
int index_of_type(labeltype label_type);
tuple<int, int > count_type_in_list_of_patterns(vector<string>  patterns,labeltype label_type);


#endif  // NCS_H_INCLUDED


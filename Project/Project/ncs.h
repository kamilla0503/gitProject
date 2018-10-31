#pragma once
#ifndef NCS_H_INCLUDED
#define NCS_H_INCLUDED
#include<string>
#include<vector>
#include<map>
#include<set>
#include <fstream>
#include<iostream>
#include<regex>
//#include<tr1>
using namespace std;

class labeltype {
public:
	string name;
	//int  isotopes;
	//bool HN, CA, CO;

	bool label_HN, label_CA, label_CO;
	// 
	labeltype(string lname = "X", bool l_HN =0, bool l_CA=0, bool l_CO=0) {
		name = lname;
		label_HN = l_HN;
		label_CA = l_CA;
		label_CO = l_CO;
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

typedef string pattern_type;

class NCS {
public:
	const vector <string> NITRO_TYPES = { "N", "D", "S", "T" };
	string name;
	vector<spectrum>spec_list;
	vector<labeltype> label_types;
	bool deuterated;
	//map<pattern_type, labeltype> label_dict
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
	bool check_power(string new_pattern,int min_depth);
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
	Scheme(string sname="", NCS sncs= NCS(), int  bsamples=0, vector <string>  bpatterns = {}); //patterns
	Scheme& operator=(Scheme& other);
	bool check_codes();
	void simplify();
	bool check_patterns(vector <string> patterns);
	void sort();
	void add_new_codes(string new_pattern);
	void add_pattern(string new_pattern); 
	bool try_pattern(string  new_pattern);
	Scheme direct_product(Scheme scheme);

};

class ELB {
public: 
	vector <string> patterns;
	string ncs_name; 
	bool deuterated;
	map <string, int> simplified;
	void simplify();
	ELB(vector <string> bpatterns, string bncs_name, bool bdeuterated = false);

	bool eq(Scheme scheme); 
	void sort();
	//bool is_subset_of(map <string, int>);

};


class BlockFinder {
	vector<labeltype> types;
	int samples;
	NCS ncs;
	int min_depth; 
	Scheme scheme;
	vector <string> patterns; //temporary 
	int depth;
	int max_depth;
	bool check_t_free;

	int  min_t_free = -1; 
	vector <int> counter; //temporary
	vector <Scheme> back_up_schemes; 
	bool  block_finder_mode; 
		




	//BlockFinder( NCS bncs, int bmin_depth, bool bblock_finder_mode, int  bmin_t_free = -1);
	BlockFinder(int bsamples, NCS bncs, int bmin_depth, bool bblock_finder_mode, int bmin_t_free);
	vector <string> generate_patterns(int  samples, bool top = true);



		//bfm? 
};




/**
class Product {
public:
	all_blocks;
	product_list;

	Product(all_blocks, product_list);



};**/


//for scheme (patterns) 
bool pattern_bigger(string pattern1, string  pattern2);
string simplify_pattern(string pattern);
string simplify_pattern2(string pattern);
#endif  // NCS_H_INCLUDED

//def read_blocks(block_file, logger = None);
//void read_blocks(string block_file,  logger, string *result,map<  , > blocks, string *ncs_name ,bool *deuterated);
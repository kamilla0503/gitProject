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
#include<tuple>



//#include<tr1>
using namespace std;

class labeltype {
public:
	//string name;
	//int  isotopes;
	//bool HN, CA, CO;
	char name; 
	bool label_HN, label_CA, label_CO;
	// 
	labeltype(char lname = 'X', bool l_HN =0, bool l_CA=0, bool l_CO=0) {
		name = lname;
		label_HN = l_HN;
		label_CA = l_CA;
		label_CO = l_CO;
	}

	bool operator<(const labeltype & t2);

};

//labeltype typeT("T", 1, 1, 0);

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
	const vector <char> NITRO_TYPES = { 'N', 'D', 'S', 'T' };
	string name;
	vector<spectrum>spec_list;
	vector<labeltype> label_types;
	bool deuterated;
	//map<pattern_type, labeltype> label_dict
	map<char, labeltype> label_dict;
	vector <char> letters;
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
	//NCS& operator=(const NCS& other);
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
	//Scheme& operator=(const Scheme& other);
	bool check_codes();
	void simplify();
	bool check_patterns(vector <string> patterns);
	void sort();
	void add_new_codes(string new_pattern);
	void add_pattern(string new_pattern); 
	bool try_pattern(string  new_pattern);
	Scheme direct_product(Scheme scheme);
	string full_str();
	//bool operator==(const Scheme & t2);
	void setscheme(string sname = "", NCS sncs = NCS(), int  bsamples = 0, vector <string>  bpatterns = {});
	bool operator<(const Scheme & t2);


};

bool operator<(const Scheme& t1, const Scheme& t2);
//bool operator==(const  Scheme& t1, const  Scheme& t2); 




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
public: 
	vector<labeltype> types;
	int samples;
	NCS ncs;
	int min_depth; 
	Scheme scheme;

	//Scheme scheme("1", ncs, samples, {});

	//vector <string> patterns; //temporary 
	//new?
	 vector <vector <string>> patterns;
	int depth;
	int max_depth;
	bool check_t_free;
	string output; 
	int  min_t_free = -1; 
	vector <int> counter = {}; //temporary
	vector <Scheme> back_up_schemes = {};
	bool  block_finder_mode; 
	int results_found; 
	map <int, set< Scheme>> result;//soe
	int iterator; 
	int index_of_type_T;
	string out1 ;
	//BlockFinder( NCS bncs, int bmin_depth, bool bblock_finder_mode, int  bmin_t_free = -1);
	BlockFinder(int bsamples, NCS bncs, int bmin_depth, bool bblock_finder_mode, int bmin_t_free);
	vector <string> generate_patterns(int  samples, bool top = true );
	void start_blockfinder();
	void maincycle();
	void go_back();
	void save_result();
	bool check_have_enought_t_free(Scheme scheme, vector<string>  patterns_left);
	void  write_result(Scheme  new_scheme); 
	vector <string> get_next_patterns(vector <string> patterns, int patterns_left, int  start_point); 
	void go_deeper(vector <string> next_patterns);
	void go_parallel();
	void check_max_depth();
	void find_schemes();
	void blockfinder_finished();
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
map <string, int>  simplify_list_of_patterns(vector<string> list_of_patterns); 
tuple<int, int > count_type_in_list_of_simplified(map <string, int> simplified, int index_of_type); 
int index_of_type(labeltype label_type);
tuple<int, int > count_type_in_list_of_patterns(vector<string>  patterns,labeltype label_type);


#endif  // NCS_H_INCLUDED

//def read_blocks(block_file, logger = None);
//void read_blocks(string block_file,  logger, string *result,map<  , > blocks, string *ncs_name ,bool *deuterated);
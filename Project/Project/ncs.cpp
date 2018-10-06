#include<string>
#include <iostream>
#include <iomanip>
#include<vector>
#include<map>
#include<set>
#include "ncs.h"

// BlockFinder project

using namespace std; 
 
spectrum::spectrum(string sname) { 
	name = sname; 
}
/**

class labeltype {
public:
	string name;
	int  isotopes;
	//bool HN, CA, CO;
	//
	labeltype(string lname = "X", int  lisotopes =0) {
		name = lname;
		isotopes = lisotopes;
	}

	bool operator<(const labeltype & t2);

};**/


bool labeltype::operator<(const labeltype& t2) {
	return (this->name < t2.name);
}

bool operator<(const labeltype& t1, const labeltype& t2) {
	return (t1.name < t2.name);
}

bool operator==(const labeltype& t1, const string& s2) {
	return (t1.name == s2);
}

bool operator==(const string& s1, const labeltype& t2) {
	return (s1 == t2.name);
}

int spectrum::has_signal(labeltype label_type_1, labeltype label_type_2) {
		vector <bool> vec1, vec2;

		vec1.push_back(label_type_1.isotopes / 100 % 10);
		vec1.push_back(label_type_1.isotopes / 10 % 10);
		vec1.push_back(label_type_1.isotopes % 10);
		vec1.push_back(label_type_2.isotopes / 100 % 10);
		vec1.push_back(label_type_2.isotopes / 10 % 10);
		vec1.push_back(label_type_2.isotopes % 10);

		vector<bool>  atom_list = vec1;

		if (name == "HSQC") {
			return int(atom_list[3]);
		}
		else if (name == "HNCO") {
			return int(atom_list[3] && atom_list[2]);
		}

		else if (name == "HNCA") {
			return int(atom_list[3] && (atom_list[1] || atom_list[4]));
		}

		else if (name == "HNCOCA") {
			return int(atom_list[3] && atom_list[2] && atom_list[1]);
		}

		else if (name == "COfHNCA") {
			return int(atom_list[3] && atom_list[1] &&  !(atom_list[2]));
		}

		else if (name == "DQHNCA") {
			return int(atom_list[3] && atom_list[1] && atom_list[4]);
		}

		else if (name == "HNCACO") {
			return int(atom_list[3] && atom_list[4] && atom_list[5]);
		}

		else if (name == "HNCAfCO") 
			//# Hypothetic spectrum, to be devepoled
			//# HN(CA - filtered)CO
			return int(atom_list[3] && !(atom_list[4]) && atom_list[5]);
	}


class constants {
	constants() {
		spectrum HSQC("HSQC");
		spectrum HNCO("HNCO");
		spectrum HNCA("HNCA");
		spectrum HNCOCA("HNCOCA");
		spectrum DQHNCA("DQHNCA");
		spectrum COfHNCA("COfHNCA");
		spectrum HNCACO("HNCACO");
		spectrum HNCAfCO("HNCAfCO");
		const vector <spectrum> basic_spectra = { HSQC, HNCO, HNCA, HNCOCA, DQHNCA, COfHNCA, HNCACO, HNCAfCO };
		/**labeltype typeX("X", 000);
		labeltype typeN("N", 100);
		labeltype typeC("C", 001);
		labeltype typeD("D", 111);
		labeltype typeA("A", 010);
		labeltype typeT("T", 110);
		labeltype typeS("S", 101);
		labeltype typeF("F", 011);
		**/



		labeltype typeX("X", 0);
		labeltype typeN("N", 100);
		labeltype typeC("C", 1);
		labeltype typeD("D", 111);
		labeltype typeA("A", 10);
		labeltype typeT("T", 110);
		labeltype typeS("S", 101);
		labeltype typeF("F", 11);

		const vector <labeltype> BASIC_TYPES = { typeX, typeN, typeC, typeD, typeA, typeT, typeS, typeF };
	}
};




	//void make_coding_table(void); 
	//name, spectra_list, label_types, deuterated = False)

	NCS::NCS(string name_ncs , vector<spectrum>spectra_list_ncs , vector<labeltype> label_types_ncs , bool deuterated_ncs ) {
		name = name_ncs;
		spec_list = spectra_list_ncs;
		label_types = label_types_ncs;
		deuterated = deuterated_ncs;
		for (labeltype l : label_types) {
			label_dict[l.name] = l;
		}
		letters = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };
		/**for (spectrum s : spec_list) {
			//vectors.push_back([0]);
			vectors.push_back({ 0 });
		}**/
		/**for (int j = 0; j < spec_list.size(); j++) {
			vectors.push_back({});
			vectors[j].push_back(0); 
		}**/

		
		make_coding_table(); 
	}

	void	NCS::make_coding_table() {
		vector <vector <string>> codes_table;
		for (int j = 0; j < label_types.size(); j++) {
			codes_table.push_back(vector<string>());
			for (int i = 0; i < label_types.size(); i++) {
				//codes_table[j].push_back({ "0" });
				//codes_table[j].push_back("0");
				codes_table[j].push_back("0");
			}
		}
		//vector<int> vec;
		//vector<string> result;
		set<string> s;
		int power;
		int code;
		//labeltype label_2, label_1;
		for (int i = 0; i < label_types.size(); i++) {
			labeltype label_2 = label_types[i];

			for (int j = 0; j < label_types.size(); j++) {
				labeltype label_1 = label_types[j];
				 vector<int> vec;
				for (spectrum spect : spec_list) {
					vec.push_back(spect.has_signal(label_1, label_2));
					
				}
				/**cout << " vec" << endl; 
				for (int m = 0; m < vec.size(); m++) {
					cout << vec[m] << "  " << endl;
				}**/
				if (find(vectors.begin(), vectors.end(), vec) != vectors.end()) {
					code = distance(vectors.begin(), find(vectors.begin(), vectors.end(), vec));
				}
				else {
					code = vectors.size();
					vectors.push_back(vec);
				}
				if (code > 9) {
					codes_table[j][i] = letters[code - 10];
				}
				else {
					codes_table[j][i] = to_string(code);
				}
			}
		}
		for (int i = 0; i < label_types.size(); i++) {
			//result = {};
			vector<string> result; 
			for (vector <string> row : codes_table) {
				result.push_back(row[i]);
			}
			set <string> s(result.begin(), result.end());
			power = s.size();
			label_power[label_types[i]] = power;
			if (power == 1 and find(NITRO_TYPES.begin(), NITRO_TYPES.end(), label_types[i]) != NITRO_TYPES.end()) {

				throw ("Error");
			}
		}
		//map <labeltype, string> subdict;
		cout << "creating map" << endl; 
		for (int i = 0; i < label_types.size(); i++) {
			labeltype  label_1 = label_types[i];
			map <labeltype, string> subdict;
			for (int j = 0; j < label_types.size(); j++) {
				labeltype label_2 = label_types[j];
				subdict[label_2] = codes_table[i][j];
				//cout << " codes" << codes_table[i][j];
				//cout << label_2.name << "it's label" << endl; 
				//cout << "FROM SUBDICT " << subdict[label_2] << endl; 
			}
			
			codes_dict[label_1] = subdict;
		}

	}



class Scheme {
public: 
	string name;
	NCS ncs;
	int samples; 
	vector <string> patterns; 
	Scheme(string sname, NCS sncs,int  bsamples, vector <string>  bpatterns) {
		name = sname; 
		patterns = bpatterns; 
		samples = bsamples;
		//ncs = NCS(sncs.name, sncs.label_types, ); 
		//ncs = sncs; 

	}





};

 //
/**
class BlockFinder {
public:
	int samples;
	bool block_finder_mode;
	NCS ncs;
	int min_depth;
	BlockFinder(int bsamples, NCS bncs, int bmin_depth, logger, elb_logger, bool bblock_finder_mode = 0) {
		samples = bsamples;
		block_finder_mode = bblock_finder_mode;
		min_depth = bmin_depth;
		ncs = bncs; //определить присваивание? 
	}
};**/































/**
class BlockFinder {
public:
int samples;
bool block_finder_mode;
NCS ncs;
int min_depth;
BlockFinder(int bsamples, NCS bncs, int bmin_depth, logger, elb_logger, bool bblock_finder_mode = 0) {
samples = bsamples;
block_finder_mode = bblock_finder_mode;
min_depth = bmin_depth;
ncs = bncs; //определить присваивание?
}
};**/

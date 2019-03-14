#include "ncs.h"

using namespace std; 
 
spectrum::spectrum(const char & sname) { 
	name = sname; 
}

spectrum::spectrum(string sname) { 
	name = sname; 
}

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

bool operator==(const labeltype& t1, const labeltype& t2) { //*
	return (t1.name == t2.name);
}

int spectrum::has_signal(labeltype label_type_1, labeltype label_type_2) {
		if (name == "HSQC") {
			return int(label_type_2.label_HN);
		}
		else if (name == "HNCO") {
			return int(label_type_2.label_HN &&  label_type_1.label_CO);
		}

		else if (name == "HNCA") {
			return int(label_type_2.label_HN && (label_type_1.label_CA || label_type_2.label_CA));
		}

		else if (name == "HNCOCA") {
			return int(label_type_2.label_HN && label_type_1.label_CO && label_type_1.label_CA);
		}

		else if (name == "COfHNCA") {
			return int(label_type_2.label_HN  && label_type_1.label_CA &&  !(label_type_1.label_CO));
		}

		else if (name == "DQHNCA") {
			return int(label_type_2.label_HN && label_type_1.label_CA &&    label_type_2.label_CA);
		}

		else if (name == "HNCACO") {
			return int(label_type_2.label_HN &&  label_type_2.label_CA && label_type_2.label_CO);
		}

		else if (name == "HNCAfCO") 
			return int(label_type_2.label_HN && !(label_type_2.label_CA) && label_type_2.label_CO);
else{
return 0;}


	}

NCS::NCS(string name_ncs , vector<spectrum>spectra_list_ncs , vector<labeltype> label_types_ncs , bool deuterated_ncs ) {
		name = name_ncs;
		spec_list = spectra_list_ncs;
		label_types = label_types_ncs;
		deuterated = deuterated_ncs;
		for (labeltype l : label_types) {
			label_dict[l.name] = l;
		}
		letters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h','i', 'j' };
		make_coding_table(); 
	}

void	NCS::make_coding_table() {
		vector <vector <string>> codes_table;
		for (int j = 0; j < label_types.size(); j++) {
			codes_table.push_back(vector<string>());
			for (int i = 0; i < label_types.size(); i++) {
				codes_table[j].push_back("0");
			}
		}
		set<string> s;
		int power;
		int code;
		for (int i = 0; i < label_types.size(); i++) {
			labeltype label_2 = label_types[i];

			for (int j = 0; j < label_types.size(); j++) {
				labeltype label_1 = label_types[j];
				 vector<int> vec;
				for (spectrum spect : spec_list) {
					vec.push_back(spect.has_signal(label_1, label_2));
				}
				
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
			vector<string> result; 
			for (vector <string> row : codes_table) {
				result.push_back(row[i]);
			}
			set <string> s(result.begin(), result.end());
			power = s.size();
			label_power[label_types[i]] = power;
			cout << "NCS POWER" << label_power[label_types[i]] << endl;

			if (power == 1 and find(NITRO_TYPES.begin(), NITRO_TYPES.end(), label_types[i]) != NITRO_TYPES.end()) {
				throw ("Error");
			}
		}
		for (int i = 0; i < label_types.size(); i++) {
			labeltype  label_1 = label_types[i];
			map <labeltype, string> subdict;
			for (int j = 0; j < label_types.size(); j++) {
				labeltype label_2 = label_types[j];
				subdict[label_2] = codes_table[i][j];
			}
			
			codes_dict[label_1] = subdict;
		}

	}

NCS& NCS::operator=(NCS& other){
	if (this != &other) {  //?
		name = other.name;
		spec_list = other.spec_list;
		label_types = other.label_types;
		deuterated = other.deuterated;
		label_dict = other.label_dict;
		letters = other.letters; 
		label_power =other.label_power;
		 codes_dict=other.codes_dict;
		 vectors = other.vectors;
	}
	return *this;
}

bool NCS::check_power( string  new_pattern, int min_power) {
	int power = 1; 
	labeltype e; 
	for (char label : new_pattern) {
		e = label_dict[label];

		power = power * label_power[  e  ];  
	} 
	return (power >= min_power); 
}

string NCS::calc_code(string pattern_1, string pattern_2) {
	string value = "";
	char s1, s2; 
	for (int i = 0; i < pattern_1.size(); i++) {
		s1 = pattern_1[i]; 
		s2 = pattern_2[i];
		value.push_back(codes_dict[label_dict[s1]][label_dict[s2]][0]); //
	}
	return value; 
}

string simplify_pattern(string pattern) { 
	string result = "";
	static map <  char, int> res = { {'X' , 0}, {'N',1}, {'C',2}, {'D',3}, {'A',4}, {'T',5}, {'S', 6}, {'F',7} }; 
	vector <int> simple_form;
	for (int i = 0; i < res.size(); i++) {
		simple_form.push_back(0);
	}
	for (char label : pattern){
		simple_form[res[label]] = simple_form[res[label]] + 1;
	}
	for ( int  a : simple_form) {
		result = result + to_string(a);
	}
	return result;
}

bool pattern_bigger(string pattern1, string  pattern2) {
	char type1, type2;
	static map<char, int>  TYPES = { {'X',0}, {'N',1}, {'C',2}, {'D', 3}, {'A',4}, {'T',5}, {'S', 6}, {'F', 7} };
	for (int i = 0; i < pattern1.size(); i++) {
		type1 = pattern1[i];
		type2 = pattern2[i];
		//!
		if (TYPES[type1] > TYPES[type2]) {
			return true;
		}
		else if (TYPES[type1] < TYPES[type2]) {
			return false;
		}
		else continue;
	}
	return true;
}


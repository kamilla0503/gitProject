#include"ncs.h"

string simplify_pattern(string pattern) { 
	string result = "";
	static map <  char, int> res = { { 'X', 0 },{ 'N',1 },{ 'C',2 },{ 'D',3 },{ 'A',4 },{ 'T',5 },{ 'S', 6 },{ 'F',7 } };
	//static  vector  <char> TYPES = { 'X', 'N', 'C', 'D', 'A', 'T', 'S', 'F' };

	vector <int> simple_form;
	for (int i = 0; i < res.size(); i++) {
		simple_form.push_back(0);
	}
	for (char label : pattern) {
		simple_form[res[label]] = simple_form[res[label]] + 1;
	}


	for (int a : simple_form) {
		result = result + to_string(a);
	}
	return result;
}

bool pattern_bigger(string pattern1, string  pattern2) {
	char type1, type2;
	static map<char, int>  TYPES = { { 'X',0 },{ 'N',1 },{ 'C',2 },{ 'D', 3 },{ 'A',4 },{ 'T',5 },{ 'S', 6 },{ 'F', 7 } };
	for (int i = 0; i < pattern1.size(); i++) {
		type1 = pattern1[i];
		type2 = pattern2[i];
		if (TYPES[type1] > TYPES[type2]) {
			return true;
		}
		else if (TYPES[type1] < TYPES[type2]) {
			return false;
		}
	}
	return true;
}
tuple<int, int > count_type_in_list_of_patterns(vector<string> patterns, labeltype label_type) {
	map <string, int>  simplified = simplify_list_of_patterns(patterns);
	int index_of_t = index_of_type(label_type);
	return count_type_in_list_of_simplified(simplified, index_of_t);
}
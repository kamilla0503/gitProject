#include"ncs.h"

ELB::ELB(vector <string> bpatterns, string bncs_name, bool bdeuterated) {
	patterns = bpatterns;
	ncs_name = bncs_name;
	deuterated = bdeuterated;
	map <string, int> simplified;
	simplify();

}

void ELB::simplify() {
	map <string, int> simplified;
	string simple_pattern;
	for (string pattern : patterns){
		simple_pattern = simplify_pattern(pattern);
		if ((simplified.size() == 0) && (simplified.find(simple_pattern) != simplified.end())) {
			simplified[simple_pattern] = simplified[simple_pattern] + 1;
		}
		else {
			simplified[simple_pattern] = 1;
		}
	}
}

bool ELB::eq(Scheme scheme) {
	return simplified == scheme.simplified;
}

void ELB::sort() {
	string temp_pattern;
	for (int i = 0; i < (patterns.size() - 1); i++) {
		for (int j = 0; j < (patterns.size() - 1-i); j++){
			if (pattern_bigger(patterns[i], patterns[i + j + 1])) {
				temp_pattern = patterns[i];
				patterns[i] = patterns[i + j + 1];
				patterns[i + j + 1] = temp_pattern;
			} 
	}
}
} 


BlockFinder::BlockFinder( int bsamples, NCS bncs, int bmin_depth, bool bblock_finder_mode, int bmin_t_free )
{

	samples = bsamples;
	ncs = bncs;
	min_depth = bmin_depth;
	check_t_free = false; 
	block_finder_mode = bblock_finder_mode;
	Scheme scheme("1", ncs, samples, {});
	depth = 0;  
	min_t_free = bmin_t_free;

	index_of_type_T = index_of_type(typeT); 


	if (min_t_free >= 0) {
		check_t_free = true;
	} 

	if (min_depth <= 1) {
		min_depth = 2;
	} 

	patterns.push_back(generate_patterns(samples ));   //[generate_patterns(self.samples)] //?
	counter.push_back(0); 
	//back_up_schemes = {};  
	results_found = 0; 
	max_depth = 0;
	iterator = 0;
	map <int, set< Scheme>> result;
	

}


vector <string> BlockFinder::generate_patterns(int  samples, bool top) {
	if (samples == 0) {
		vector <string> new_set = { "" };
			
		return new_set;
	}
	vector <string>  current_set = generate_patterns(samples - 1, top = false);
	vector <string>new_set;
	new_set = { };


	string new_pattern;
	for (string item : current_set) {
		for (labeltype option : ncs.label_types) {
			new_pattern = item + option.name;
			if (top) {
				if (ncs.check_power(new_pattern, min_depth) ){
					new_set.push_back(new_pattern); 
				}
		}
			else {
				new_set.push_back(new_pattern);
			} 
	}
	} 


	return new_set;


}
//?

int index_of_type(labeltype label_type) {
	labeltype typeX("X", 0, 0, 0);
	labeltype typeN("N", 1, 0, 0);
	labeltype typeC("C", 0, 0, 1);
	labeltype typeD("D", 1, 1, 1);
	labeltype typeA("A", 0, 1, 0);
	labeltype typeT("T", 1, 1, 0);
	labeltype typeS("S", 1, 0, 1);
	labeltype typeF("F", 0, 1, 1);

	static map<labeltype, int>  basic_types = { {typeX, 0}, { typeN,1 } , {typeC, 2} , {typeD, 3} , {typeA, 4} , {typeT, 5} ,{ typeS, 6}, {typeF, 7} };

	return basic_types[label_type]; 
} 



/**
void BlockFinder::start_blockfinder() {
	if (check_t_free) {
		cout << "started " << samples << " " << min_depth << " " << min_t_free << endl; 
	}





}**/


/**
void BlockFinder::maincycle() {
	vector<string> patternscurrent;
	int start_point;
	int patterns_left; 
	while (true) {
		patternscurrent = patterns[depth];
		if (depth == 0 && counter[0] + min_depth > patternscurrent.size()) {
			break;
		}

		start_point = 1 + counter[depth];
		patterns_left = patternscurrent.size() - start_point;


		back_up_schemes.push_back(scheme);
		scheme.add_pattern(patternscurrent[counter[depth]]);

		if (patterns_left < min_depth - depth - 1){
			go_back();
			continue;
		}

		if (patterns_left == 0) {
			if (scheme.patterns.size() >= min_depth){
				save_result();
			}
				go_back();
				continue;
		}



		next_patterns = self.get_next_patterns(patterns, patterns_left, start_point)

			flag_t_free = True
			if self.check_t_free:
		flag_t_free = self.check_have_enought_t_free(self.scheme, next_patterns)

			if next_patterns and flag_t_free :
				self.go_deeper(next_patterns)
			else :
				if len(self.scheme.patterns) >= self.min_depth :
					self.save_result()
					self.go_parallel()


					self.check_max_depth()






	}



}
**/



void BlockFinder::go_back() {
	depth = -1;
	patterns.pop_back();
	back_up_schemes.pop_back();
	scheme = back_up_schemes[back_up_schemes.size() - 1];
	back_up_schemes.pop_back();

}
/**
void BlockFinder::save_result(Scheme nscheme) {
	if () {

		return; 
	}






}**/




bool BlockFinder::check_have_enought_t_free(Scheme scheme, vector<string>  patterns_left) {
	tuple <int, int> t;
	t = count_type_in_list_of_simplified(scheme.simplified, index_of_type_T); 
	int scheme_t = get<0>(t); 
	int scheme_t_free = get<1>(t); 
	tuple <int, int> t2; 
	t2 = count_type_in_list_of_patterns(patterns_left, typeT); 
	int left_t = get<0>(t2);
	int left_t_free = get<1>(t2);

	return (scheme_t_free + left_t_free >= min_t_free); 
}

map <string, int>  simplify_list_of_patterns(vector<string> list_of_patterns) {
	map <string, int> simplified;
	string simple_pattern;
	for (string pattern : list_of_patterns) {
		simple_pattern = simplify_pattern(pattern);
		if(  simplified.size() != 0 &&   simplified.count(simple_pattern)!=0  ){
			simplified[simple_pattern] = simplified[simple_pattern] + 1;
	}
		else {
			simplified[simple_pattern] = 1;
		} 
	}

	return simplified;

}

tuple<int, int > count_type_in_list_of_simplified(map <string, int> simplified, int index_of_type) {
	int count_type = 0;
	int count_all = 0;
	int has_t;
	for(  auto sp : simplified) {
		has_t = 0;
			if (int(sp.first[index_of_type])) {
				has_t = 1;
			}
			count_type = count_type + has_t * sp.second;
			count_all = count_all  + sp.second;
	}
	return  make_tuple(count_type, count_all - count_type);
}

tuple<int, int > count_type_in_list_of_patterns(vector<string> patterns, labeltype label_type) {


	map <string, int>  simplified = simplify_list_of_patterns(patterns);
	int index_of_t = index_of_type(label_type);
	return count_type_in_list_of_simplified(simplified, index_of_t);


}
/**
tuple<int, int > count_type_in_list_of_simplified(map <string, int> simplified, int  index_of_type) {
	int count_type = 0;
	int count_all = 0;
	int has_t;
	for (auto i : simplified) {
		has_t = 0;
		if (int(i.first[index_of_type])) {
			has_t = 1;
		}
		count_type += has_t * i.second;
		count_all += pattern_count; 



	}





}
**/

/**
bool ELB::is_subset_of(map <string, int> other_simple) {
	for( auto pattern : simplified  ){
		if (find(other_simple.begin(), other_simple.end(), pattern) == other_simple.end()) {
			return false;
		}
		if (pattern.second > other_simple[pattern.first]) {
			return false;
		}
	} 
	return true;

} **/
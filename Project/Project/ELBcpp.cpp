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


BlockFinder::BlockFinder( int bsamples, NCS bncs, int bmin_depth, bool bblock_finder_mode, int bmin_t_free)
{	
        samples = bsamples;
	ncs = bncs;
	min_depth = bmin_depth;
	check_t_free = false; 
	block_finder_mode = bblock_finder_mode;
	scheme.setscheme("1", ncs, samples, {});
	//scheme = Scheme("1", ncs, samples, {});
	//cout << "check scheme creating " << scheme.samples << " " << scheme.name <<endl; 
	depth = 0;  
	min_t_free = bmin_t_free;

	index_of_type_T = index_of_type(labeltype('T', 1, 1, 0));

	//cout << " see T " << index_of_type_T << endl; 
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
	result_string = "[NCS = " + ncs.name + "]\n"+
	                "[Deuterated = " + (ncs.deuterated?"True":"False") + "]\n";
	
	out1 = "";
	start_time = clock();
	//map <int, set< Scheme>> result;
	

}


vector <string> BlockFinder::generate_patterns(int  bsamples, bool top ) {
	vector <string> new_set;
	vector <string>  current_set;
	//cout << top << endl; 
	if (bsamples == 0) {
		new_set = { "" };
		//cout << top << " it samples = 0" << endl;
		return new_set;
	}
	
	current_set = generate_patterns(bsamples - 1, false);
	//vector <string>new_set;
	new_set = { };


	string new_pattern;
	for (string item : current_set) {
		//cout <<"item     "<<item << endl;
		//cout << "cycle started" << endl;
		//cout << " it is top" << top << endl;
		for (labeltype option : ncs.label_types) {
			new_pattern = item + option.name;
			//cout << " new_pattern " << new_pattern << endl;
			if (top==true ) {
				//cout << " top is true" << endl; 
				if (ncs.check_power(new_pattern, min_depth) ){
					//cout<< "check _ power " << ncs.check_power(new_pattern, min_depth )<< endl;
					new_set.push_back(new_pattern); 
					//cout << "find problem " << new_set[0] << endl; 
				}
		}
			else {
				//cout << "I'm here" << endl; 
				new_set.push_back(new_pattern);
			} 
		}
	} 

	//cout << "problems or not " << new_set[0] << endl; 
	return new_set;


}
//?

int index_of_type(labeltype label_type) {
	labeltype typeX('X', 0, 0, 0);
	labeltype typeN('N', 1, 0, 0);
	labeltype typeC('C', 0, 0, 1);
	labeltype typeD('D', 1, 1, 1);
	labeltype typeA('A', 0, 1, 0);
	labeltype typeT('T', 1, 1, 0);
	labeltype typeS('S', 1, 0, 1);
	labeltype typeF('F', 0, 1, 1);
	
	static map<char, int>  basic_types = { {typeX.name, 0}, { typeN.name,1 } , {typeC.name, 2} , {typeD.name, 3} , {typeA.name, 4} , {typeT.name, 5} ,{ typeS.name, 6}, {typeF.name, 7} };

	return basic_types[label_type.name]; 
} 




void BlockFinder::start_blockfinder() {
	if (check_t_free) {
		cout << "started samples =" << samples << " min depth = " << min_depth << " min_t_free=" << min_t_free << endl; 
		out1 = "started samples =" + to_string(samples) + " min depth = " + to_string(min_depth) + " min_t_free=" + to_string(min_t_free);
	}
	else {
		out1 = "started samples =" + to_string(samples) + " min depth = " + to_string(min_depth);
		cout << "started samples =" << samples << " min depth = " << min_depth << endl;
	}
	cout << " total number of patterns is  " << patterns[0].size() << endl; 
}


void BlockFinder::maincycle() {
	vector<string> patternscurrent, next_patterns;
	int start_point;
	int patterns_left; 
	bool flag_t_free;
	int w = 0;
	while (true) {
	        next_iteration_output();

		//cout << "cycle started and schame samples = " << scheme.samples << endl; 
		patternscurrent = patterns[depth];
		//cout << patternscurrent[0] << " patternscurrent [ 0 ] " << endl; 
		if (depth == 0 && ( (counter[0] + min_depth )> patternscurrent.size())) {
			break;
		}

		//cout << "depth = " << depth << endl; 


		start_point = 1 + counter[depth];
		patterns_left = patternscurrent.size() - start_point;
		//cout << " patterns_left " << patterns_left << endl;
		//cout << " see counter" << endl; 
		/**
		for (int q = 0; q < counter.size(); q++) {
			cout << counter[q] << endl; 
		}
		**/

		w = w + 1; 
		back_up_schemes.push_back(scheme);
		//cout << "scheme is apeended " << scheme.samples <<""   << scheme.name <<endl; 
		scheme.add_pattern(patternscurrent[counter[depth]]);
		//cout << "check cs for first save " << scheme.patterns.size() << " " << min_depth << endl; 
		if (patterns_left < (min_depth - depth - 1)   ) {
			go_back();
			//w = w + 1;
			continue;
		}
		if (patterns_left == 0) {
			if (scheme.patterns.size() >= min_depth) {
				//cout << "save or not " << endl;
				save_result();
			}
			go_back();
			//w = w + 1;
			continue;
		}

		next_patterns = get_next_patterns(patternscurrent, patterns_left, start_point);

		flag_t_free = true;
		if (check_t_free) {
			flag_t_free = check_have_enought_t_free(scheme, next_patterns);
		}

		if ( next_patterns.size() != 0 && flag_t_free){
			w = w + 1;
			go_deeper(next_patterns);
			

		}
		else {
			if (scheme.patterns.size() >= min_depth) {
				//cout << "save or not  2" << endl;
				save_result();
			}
			go_parallel();
			

		}
		check_max_depth();
	
	}

	cout << " we went deeper " << w << endl;

}


void BlockFinder::next_iteration_output()
{
    iterator++;
    if (iterator % 10000 == 0) {
      ostringstream log;
      log<< "[BlockFinder" << to_string(samples) << "]";
      log<< setw(9) << iterator;
      time_t now = clock();
      double time_in_run = (double)(now - start_time) / CLOCKS_PER_SEC;
      //out += to_string
      log << setw(8) << setprecision(2) << fixed << time_in_run << " sec";
      log << " max_P=" << setw(2) << setiosflags(ios::left) << max_depth + 1;
      cout << log.str() << endl;
    }
}

void BlockFinder::go_parallel() {
	scheme =back_up_schemes[depth];
	back_up_schemes.pop_back();
	counter[depth] = counter[depth] + 1;
}

void BlockFinder::check_max_depth() {
	if (depth > max_depth) {
		max_depth = depth;
		if (block_finder_mode) {
			out1 = "[BlockFinder" + to_string(samples) + " ] New max depth:" + to_string(max_depth); 
		}
	}

} 

vector <string> BlockFinder::get_next_patterns(vector <string> patterns, int patterns_left, int  start_point) {
	vector <string> next_patterns ;
	for (int i = 0; i < patterns_left; i++)  {
		if( scheme.try_pattern(patterns[i + start_point])) {
			next_patterns.push_back(patterns[i + start_point]);
		}
	}
	/**for (int i = 0; i < next_patterns.size(); i++) {
		cout << next_patterns[i] << " " << endl;
	}**/
	//cout << endl;

	return next_patterns;
}

void BlockFinder::go_deeper(vector <string> next_patterns) {
	patterns.push_back(next_patterns);
	counter.push_back(0);
	depth = depth + 1;
}

void BlockFinder::find_schemes() {
	start_blockfinder();
	maincycle();
	blockfinder_finished();
}




void BlockFinder:: blockfinder_finished() {
	out1 = "[BlockFinder] finished search in" + to_string(samples) + "samples after " + to_string(iterator) + " iterations " + to_string(results_found) + " ELB schemes found";
	/**for (auto c : result) {
		for ( auto i: c.second ) {
			cout << i.samples << " " << endl; 



		}
	}**/
}

void BlockFinder::go_back() {
	depth = depth -1;
	patterns.pop_back();
	counter.pop_back();
	counter[counter.size() - 1] = counter[counter.size() - 1] + 1;


	back_up_schemes.pop_back();
	scheme = back_up_schemes[back_up_schemes.size() - 1];
	back_up_schemes.pop_back();

}

void BlockFinder::save_result() {
	if (check_t_free && !(check_have_enought_t_free(scheme, {}))) {

		return; 
	}
	int depth_of_scheme;
	depth_of_scheme= scheme.patterns.size();
	Scheme new_scheme;
	new_scheme = scheme;
	new_scheme.sort();
	/**for (int i = 0; i < new_scheme.patterns.size(); i++) {
		cout << new_scheme.patterns[i] << " ";

	}**/
	//cout << endl;
	// << "check conditions " << (result.find(depth_of_scheme) != result.end()) << depth_of_scheme << endl;
	
	if(	result.find(depth_of_scheme) != result.end() ){ //casd 
		//cout << " conditions are ok  " << endl; 

		//cout << " is there new_scheme in set ?" << (result[depth_of_scheme].count(new_scheme)) << endl;
		//if (find(result[depth_of_scheme].begin(), result[depth_of_scheme].end(), new_scheme) != result[depth_of_scheme].end()) {
		if (result[depth_of_scheme].find(new_scheme) == result[depth_of_scheme].end()) {
		//if (result[depth_of_scheme].count(new_scheme) == 0) {
			result[depth_of_scheme].insert(new_scheme);
			write_result(new_scheme); //something wrong!!!!
			//cout << " that if " << endl; 
		}

		
		//result[depth_of_scheme].insert(scheme);
		//result[depth_of_scheme].insert(new_scheme); // what if change 
		//write_result(new_scheme); 
		
	} 
	else {
		result[depth_of_scheme] = { new_scheme }; 
		write_result(new_scheme);
		//cout << " other if! " << endl;
	}
}




bool BlockFinder::check_have_enought_t_free(Scheme scheme, vector<string>  patterns_left) {
	tuple <int, int> t;
	t = count_type_in_list_of_simplified(scheme.simplified, index_of_type_T); 
	int scheme_t = get<0>(t); 
	int scheme_t_free = get<1>(t); 
	tuple <int, int> t2; 
	t2 = count_type_in_list_of_patterns(patterns_left, labeltype('T', 1, 1, 0));
	int left_t = get<0>(t2);
	int left_t_free = get<1>(t2);
	//cout << "check_have_enought_t_free " << (scheme_t_free + left_t_free >= min_t_free) << endl; 
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

	//cout << "T or what " << label_type.name << endl; 
	map <string, int>  simplified = simplify_list_of_patterns(patterns);
	int index_of_t = index_of_type(label_type);
	//cout << "count_type_in_list_of_patterns " << get<0>(count_type_in_list_of_simplified(simplified, index_of_t)) << " " << get<1>(count_type_in_list_of_simplified(simplified, index_of_t)) << endl; 
	return count_type_in_list_of_simplified(simplified, index_of_t);


}

void  BlockFinder::write_result(Scheme  new_scheme) {
	results_found = results_found + 1;
	result_string += new_scheme.full_str();
	//cout << new_scheme.samples << "samples from new_scheme " << endl; 

}






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

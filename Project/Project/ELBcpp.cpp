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

	if (min_t_free >= 0) {
		check_t_free = true;
	} 

	if (min_depth <= 1) {
		min_depth = 2;
	} 



	//counter.push_back(0); 
	
//result = {};
		//self.results_found = 0
		//self.output = ''
		//self.iterator = 0
		//self.timer = time.time()
		//self.block_finder_mode = block_finder_mode
		//self.outputer = outputer


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
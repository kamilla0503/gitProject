#pragma once
#include"Scheme.h"

class BlockFinder {
public:
	BlockFinder(int bsamples, NCS bncs, int bmin_depth, bool bblock_finder_mode, int bmin_t_free);
	vector<labeltype> types;
	int samples;
	NCS ncs;
	int min_depth;
	Scheme scheme;
	vector <vector <string>> patterns;
	int depth;
	int max_depth;
	bool check_t_free;
	string result_string;
	int  min_t_free = -1;
	vector <int> counter = {};
	vector <Scheme> back_up_schemes = {};
	bool  block_finder_mode;
	int results_found;
	map <int, set< Scheme>> result;
	int iterator;
	int index_of_type_T;
	string out1;
	time_t start_time;
	vector <string> generate_patterns(int  samples, bool top = true);
	void start_blockfinder();
	void maincycle();
	void next_iteration_output();
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
};
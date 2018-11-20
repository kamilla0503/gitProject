#include<string>
#include <iostream>
#include <iomanip>
#include<vector>
#include<map>
#include<set>
#include <algorithm>

#include "ncs.h"

using namespace std; 
 
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



/**
Scheme& Scheme::operator=(  const Scheme& other) {
	if (this != &other) {  //?
		name = other.name;
		ncs = other.ncs;
		samples = other.samples;
		patterns = other.patterns;
		codes = other.codes;
		new_codes = other.new_codes;
		simplified = other.simplified;
		good = other.good;
	}
	return *this;
}**/





























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

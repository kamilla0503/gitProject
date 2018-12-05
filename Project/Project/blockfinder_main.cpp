#include<time.h> 
#include<iomanip>
#include<iostream>
#include <sstream>
#include"blockfinder.h"

using namespace std;

int main(int argc, char *argv[]) {
	string name_ncs;
	int begin, end, samples, min_depth; 
	cout << "started " << argc << endl;
	if (argc <= 1) {


		cout << "No arguments" << endl; 


		return -1; 
	}
	else if(argc ==4){
		name_ncs = argv[1];
		stringstream convert(argv[2]);
		convert >> samples; 
		stringstream convertdepth(argv[3]);
		convertdepth >> min_depth;
		cout << "readed" << endl;
	}

	getchar();

	return 0;
}
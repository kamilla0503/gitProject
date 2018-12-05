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
	else {
		name_ncs = argv[1];
		stringstream convert(argv[2]);
		convert >> samples;
		stringstream convertdepth(argv[3]);
		convertdepth >> min_depth;
		
		stringstream convertbegin(argv[4]);
		convertbegin >> begin;

		stringstream convertend(argv[5]);
		convertend >> end; 

		cout << "readed" << endl;
	}

	NCS test_nc2 = get_NCS(name_ncs);


	for (labeltype type_1 : test_nc2.label_types)
		cout << setw(1) << type_1.name << " ";
	cout << endl;
	for (labeltype type_1 : test_nc2.label_types) {
		cout << setw(1) << type_1.name << " ";
		for (labeltype type_2 : test_nc2.label_types) {
			cout << test_nc2.codes_dict[type_1][type_2] << " ";
		};
		cout << endl;
	}
	cout << " vectors: " << endl;
	cout << setw(7) << "Code ";
	for (spectrum s : test_nc2.spec_list) {
		//cout << setw(7) << s.name << " ";
		cout << s.name << " ";
	}
	cout << endl;


	getchar();

	return 0;
}
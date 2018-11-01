#include"ncs.h"
#include<string>
#include<vector>
#include<map>

#include<iomanip>
#include<iostream>
//
using namespace std; 

int main(int argc, char **argv)
{
	vector<spectrum> nc2_spectra;
	vector<labeltype> nc2_labeltype;
	string nc2_name("NC2");

	nc2_spectra.push_back(spectrum("HSQC"));
	nc2_spectra.push_back(spectrum("HNCO"));
	//nc2_spectra.push_back(spectrum("HNCA"));
	//nc2_spectra.push_back(spectrum("HNCOCA"));
	//nc2_spectra.push_back(spectrum("DQHNCA"));
	//nc2_spectra.push_back(spectrum("COfHNCA"));
	//nc2_spectra.push_back(spectrum("HNCACO"));
	//nc2_spectra.push_back(spectrum("HNCAfCO"));





	nc2_labeltype.push_back(labeltype("X", 0, 0, 0));
	nc2_labeltype.push_back(labeltype("N", 1,0,0));
	nc2_labeltype.push_back(labeltype("C",0, 0, 1));

	NCS test_nc2(nc2_name, nc2_spectra, nc2_labeltype);
	NCS newtest = test_nc2;
	cout << " Size of label_types: " << newtest.label_types.size() << endl;
	cout << " Size of spec_list: " << newtest.spec_list.size() << endl;
	cout << " codes_dict: " << endl;
	cout << "  ";
	//cout << " see " << endl; 
	//cout << test_nc2.codes_dict[nc2_labeltype[0]][nc2_labeltype[0]] << " ";
	cout << " see " << endl;
	cout << newtest.codes_dict[nc2_labeltype[0]][nc2_labeltype[0]] << " ";

	//map < NCS, int > s;
	//s[test_nc2] = 3;
	//cout << " * " << s[test_nc2] << endl; 


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

	for (int code = 0; code < test_nc2.vectors.size(); code++) {
		//cout << setw(7) << code << " ";
		cout << code << " ";
		vector <int> v = newtest.vectors[code];
		for (int peak : v) {
			cout << setw(10) << peak << " ";
		}
		cout << endl;
	}

	getchar();

	string s1 = "NNNCCCXXX";
	string s2 = "NCXNCXNCX";
	string code = test_nc2.calc_code(s1, s2);
	cout << "s1=  " << s1<<endl;
	cout << "s2=  " << s2 << endl;
	cout << "code=" << code << endl;


	string r1 = simplify_pattern2(s1);

	string r2 = simplify_pattern2(s2);
	cout << "Sp " << r1 << endl; 
	cout << "Sp " <<  r2 << endl;

	Scheme scheme("1", test_nc2, 2, {});
	Scheme scheme2 = scheme;
	set <Scheme> s;
	s.insert(scheme); 
	//s.insert(scheme2);


	getchar();

	return 0;
}


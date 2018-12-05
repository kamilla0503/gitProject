#include"ncs.h"


NCS get_NCS(string name) {
	//NCS ncs; 
	vector<spectrum> nc2_spectra;
	vector<labeltype> nc2_labeltype;

	if (name == "NC2") {
		nc2_labeltype.push_back(labeltype('X', 0, 0, 0));
		nc2_labeltype.push_back(labeltype('N', 1, 0, 0));
		nc2_labeltype.push_back(labeltype('C', 0, 0, 1));
		nc2_spectra.push_back(spectrum("HSQC"));
		nc2_spectra.push_back(spectrum("HNCO"));
		NCS ncs(name, nc2_spectra, nc2_labeltype);
		return ncs;
	}



	
}
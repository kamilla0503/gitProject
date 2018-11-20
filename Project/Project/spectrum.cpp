#include"Spectrum.h"

spectrum::spectrum(string sname) {
	name = sname;
}


int spectrum::has_signal(labeltype label_type_1, labeltype label_type_2) {
	vector <bool> vec1, vec2;
	
	if (name == "HSQC") {
		return int(label_type_2.label_HN);
	}
	else if (name == "HNCO") {
		return int(label_type_2.label_HN &&  label_type_1.label_CO);
	}

	else if (name == "HNCA") {
		return int(label_type_2.label_HN && (label_type_1.label_CA || label_type_2.label_CA));
	}

	else if (name == "HNCOCA") {
		return int(label_type_2.label_HN && label_type_1.label_CO && label_type_1.label_CA);
	}

	else if (name == "COfHNCA") {
		return int(label_type_2.label_HN  && label_type_1.label_CA && !(label_type_1.label_CO));
	}

	else if (name == "DQHNCA") {
		return int(label_type_2.label_HN && label_type_1.label_CA &&    label_type_2.label_CA);
	}

	else if (name == "HNCACO") {
		return int(label_type_2.label_HN &&  label_type_2.label_CA && label_type_2.label_CO);
	}

	else if (name == "HNCAfCO")
		return int(label_type_2.label_HN && !(label_type_2.label_CA) && label_type_2.label_CO);
}

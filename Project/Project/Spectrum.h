#pragma once
#include<vector>
#include"labeltype.h"
class spectrum {
public:
	string name;
	spectrum(string sname);
	int has_signal(labeltype label_type_1, labeltype label_type_2);
};
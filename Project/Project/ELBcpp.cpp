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
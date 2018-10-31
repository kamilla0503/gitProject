#include"ncs.h"

/**
void read_blocks(string block_file, logger, string *result, blocks, string *ncs_name, bool *deuterated) {
	ifstream f;
	int i = 0;
	bool deuterated = false;
	bool deuterated_found = false;
	vector<string> lines; 
	string temp; 
	f.open(block_file);
	if (!f.is_open()) {
		cout << "File was not opened " << endl;
	}
	else {
		while (!f.eof()) {
			 getline(f, temp);
			 lines.push_back(temp);

		}
	}
	int blocks_num = 0;
	bool NCS_found = false;
	string ncs_re = "\\[\\s*NCS\\s*=\\s*(\\w+)\\s*\\]";


}

**/

/**
int main() {
	string block_file = "qwerty.txt";
	ifstream f;
	int i = 0;
	bool deuterated = false;
	bool deuterated_found = false;
	vector<string> lines;
	string temp;
	f.open(block_file);
	if (!f.is_open()) {
		cout << "File was not opened " << endl;
	}
	else {
		while (!f.eof()) {
			getline(f, temp);
			lines.push_back(temp);

		}
	}

	for (string s : lines) {
		cout << s << endl;
	}
	getchar(); 
	return 0; 
}
**/



/**

void func(int *x, int *y)
{
	*x += 5;
	*y += 3;
}

int main(void)
{
	int a = 5;
	int b = 10;
	std::cout << "Before: a=" << a << "; b=" << b;
	std::cout << std::endl;

	func(&a, &b);

	std::cout << "After: a=" << a << "; b=" << b;
	std::cout << std::endl;
	return 0;
}



**/
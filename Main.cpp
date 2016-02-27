#include <iostream>
#include <assert.h>

using namespace std;

void print_logo();
void help();
int load();
void load_link();
void dict_print_all();
void zoogle(string key);

int main(int argc, char const *argv[]) {

	print_logo();
	load_link();
	load();
    dict_print_all();
	string key;
	while (true) {
		getchar();
		key.clear();
		print_logo();
		cout<<"Zoogle it$ ";
		while (key=="") getline(cin, key);
		if (key == ":q") break;
		if (key == "--help") {
			help();
			continue;
		}
		zoogle(key);
		fflush(stdout);
	}
    return 0;
}

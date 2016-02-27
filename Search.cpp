#include "Dictionary.h"
//#include <c>
#include <sstream>

#define RED		"\033[31m"			/* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define RESET   "\033[0m"


void read_pos(int pos);
extern set <string> exclude;
extern map <string, Node> dict;
set <string> LogOpe = {"&", "|", "-"};
int prec(string sym) {
	if (sym=="-") return 3;
	if (sym=="&") return 2;
	if (sym=="|") return 1;
	return 0;
}
//typedef vector <string> STR_VEC;
vector <string> tokens;

int loc_dom(int p, int q) {
	int loc = p;
	for (int i=p; i<q; i++) {
		if ((prec(tokens[i]))>prec(tokens[loc])){
			loc = i;
		}
	}
	return loc;
}
bool my_cmp(Doc doc1, Doc doc2) {
	//return (doc1.docnum < doc2.docnum) || (doc1.docnum==doc2.docnum && doc1.type!=doc2.type);
	return (doc1.weight > doc2.weight);
}
DOCS calc(int p, int q) {
	DOCS result;
	if (p==q) {
		auto search = dict.find(tokens[p]);
		//return result->second.doc;
		//cout << search->first <<endl;
		if (search==dict.end()) {
			result.clear();
			return result;
		}
		sort(search->second.doc.begin(), search->second.doc.end(), my_cmp);
		result = search->second.doc;
	}
	else {
		int loc = loc_dom(p, q);
		DOCS docs1 = calc(p, loc-1);
		DOCS docs2 = calc(loc+1, q);
		switch (tokens[loc][0]) {
			case '&':
				set_intersection(docs1.begin(), docs1.end(), docs2.begin(), docs2.end(), back_inserter(result), my_cmp);
				break;
			case '-':
				set_difference(docs1.begin(), docs1.end(), docs2.begin(), docs2.end(), back_inserter(result), my_cmp);
				break;
			case '|':
				set_union(docs1.begin(), docs1.end(), docs2.begin(), docs2.end(), back_inserter(result), my_cmp);
				break;
		}

	}
	return result;
}
#define PAGE_SIZE 6
bool is_end(int item, int nr_result) {
	if (item >= nr_result) {
		cout<<RED<<"You have reached the end of the list."<<RESET<<endl;
		return true;
	}
	else return false;
}
bool is_start(int item) {
	if (item <= 0) {
		cout<<RED<<"You have reached the start of the list."<<RESET<<endl;
		return true;
	}
	else return false;
}

void zoogle(string key) {
	//assert(0);
	clock_t c_start = clock();

	int i=0;						//Caps fuzzy
	while (i<key.length()) {
		key[i]=tolower(key[i]);
		i++;
	}

	stringstream expr;
	expr.clear();
	tokens.clear();
	expr<<key;
	string buf;
	while (expr.good()) {
		expr>>buf;					//deal with defaut '&'
		//cout<<"buffffff:"<<buf<<endl;
		if (!tokens.empty() && prec(tokens.back())==0 && prec(buf)==0) {
			tokens.push_back("&");
		}
		tokens.push_back(buf);
	}

	DOCS search = calc(0, tokens.size()-1);
	int nr_result = search.size();
	cout<<GREEN<<"About "<<nr_result<<" results ";
	clock_t c_end = clock();
	double cost_time = 1.0 * (c_end-c_start) / CLOCKS_PER_SEC;
	cout << "( "<< cost_time << " seconds)\n"<<RESET;

	if (tokens.size()==1 && exclude.find(key) != exclude.end()){
		cout<<RED<<"Please input a meaningful word!"<<RESET<<endl;
	}
	else
	//auto search = dict.find(key);
	if (search.empty()){
		cout<<"Sorry, your search \""<<key<<"\" did not match any documents.\n"<<RESET;
		return;
	}
	else {
		cout<<key<<":"<<endl;
		//int nr_result = search->second.count;
		int item = 0;
		while (true) {
			if (is_end(item, nr_result)) return;
			auto p = search[item];
			cout<<GREEN<<"No."<<p.docnum<<RESET<<endl;
			read_pos(p.pos);
			item++;
			if (item % PAGE_SIZE == 0) {		//turning page
				cout<<"About "<<nr_result<<" results\n";
				//fflush(stdin);
				char ch = 0;
				ch = getchar();
				switch (ch) {
					case '\n':
						//item += PAGE_SIZE;
						system("clear");
						continue;
						if (is_end(item, nr_result)) return;
						break;
					case 'k':
						item -= PAGE_SIZE * 3;
						system("clear");
						cout<<"page up"<<endl;
						if (is_start(item)) return;
						break;
					case 'q':
						system("clear");
						return;
					default :
						item -= PAGE_SIZE;
						break;

				}
			}
		}
	}
	return;
}

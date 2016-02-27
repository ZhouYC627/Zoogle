#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <queue>


using namespace std;

//#define DOCNAME "../dataset/documents.txt"
//#define LINKNAME "../dataset/link.txt"
#define DOCNAME "../dataset/stackoverflow.txt"
#define LINKNAME "../dataset/mylink.txt"
#define TIT_LEN 7

void dict_insert(string word, int no, int type, int pos);
void link_insert(int number, int nr_link, string content);

void print_logo() {
	system("clear");
    cout<<"===================================="<<endl;
    cout<<"|         Welcome to Zoogle!       |"<<endl;
    cout<<"===================================="<<endl;
}
void help() {
	system("clear");
	cout<<"Zoogle\t A Quick Search Engine.\nCreated by Zhou.Y.C on 12/30/15.\nAll rights reserved.\n\n";
	cout<<"Support Boolean Retrieval.\nOperation\n\t'A & B' :\treturns the union of sets A and B.\n\t'A | B' :\treturns the intersection of sets A and B\n\t'A - B' :\treturns the difference of sets A and B\n\n";
	cout<<"Results Display\n\tk: \tPage Up\n\tj: \tPage Down\n\tq: \tReturn to Menu\n\tSort by Importance of Items.\n\n";
	cout<<"Input ':q' to quit\n"<<endl;
	//getchar();
}

int load() {
	clock_t c_start = clock();
	ifstream fin;
    fin.open(DOCNAME);
    if (!fin.is_open()) {
        cerr<<"Not open."<<endl;
        return 0;
    }
    int NR_art = 0;

    cout<<"Loading";
	string buf, title, abstract;
	getline(fin, buf);
    while (!fin.eof()) {
        NR_art++;
        if (NR_art%100==0) {
			printf(".");
        	fflush(stdout);
		}
        //getline(fin, buf);

		int filepos = fin.tellg();
		getline(fin, title);
		//cout<<title<<endl;
        stringstream div_str;
        div_str<<title;                 //split title
        while (div_str.good()) {
            string word;
            div_str>>word;
            if (word.length()!=0) dict_insert(word, NR_art, 0, filepos);
			word.clear();
        }

		//filepos = fin.tellg();
		div_str.clear();                //split abstract
		do{
			getline(fin, abstract);
        	div_str<<abstract;
		}while(!fin.eof() && abstract.substr(0,2)!="##");
        while (div_str.good()) {
            string word;
            div_str>>word;
            if (word.length()!=0) dict_insert(word, NR_art, 1, filepos);
        }

		//getline(fin, buf);				//empty line


    }
	fin.close();
	cout<<"\nDone!";
	clock_t c_end = clock();
	double cost_time = 1.0 * (c_end-c_start) / CLOCKS_PER_SEC;
	cout<<"( "<<cost_time<< " seconds)\n";
	//cout<<endl;
	return NR_art;
}

#define MAX_INT 2147483647
#define MAX_LEN 60
extern vector <string> tokens;
string transform(string word);
bool is_key(string key) {
	key = transform(key);
	for (auto it = tokens.begin(); it!=tokens.end(); it++){
		if (key == *it)
		return true;
	}
	return false;
}
#define RED		"\033[31m"			/* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define LIGHT_BLUE "\033[1;34m"	/* LIGHT_BLUE */
#define RESET   "\033[0m"

void read_pos(int pos) {
	ifstream fin;
	fin.open(DOCNAME);					//locate keywords position
	fin.seekg(pos);
	string buf;

	getline(fin, buf);
	stringstream title;					//title
	title<<buf;
	while (title.good()) {
		title>>buf;
		if (is_key(buf)) {
			cout<<YELLOW<<buf<<" ";
		}
		else {
			cout<<LIGHT_BLUE<<buf<<" ";
		}
		buf.clear();
	}
	cout<<RESET<<endl;

	//getline(fin, buf);
	stringstream abstract, line;					//if abstract contains key words
	string word;
	//buf.clear();
	getline(fin, buf);
	while(!fin.eof() && buf.substr(0,2)!="##"){
		abstract<<buf;
		getline(fin, buf);
	}
	line.str(abstract.str());
	//abstract>>buf;
	//line<<buf;
	int low = MAX_INT, high = 0;
	int count = 0;
	bool flag = false;
	while (line.good()) {
		line>>word;
		count++;
		if (is_key(word)) {
			if (count < low) low = count;
			if (count > high) high = count;
		}
		word.clear();
	}
	if (low == MAX_INT) {						//no content in abstract
		low = 0;
		high = MAX_LEN / 3;
	}
	low -= MAX_LEN / 3;							//reset counter
	if (low < 0) low = 0;
	else cout<<"...";
	//if ((high - low)> MAX_LEN) high = low + MAX_LEN;
	count = 0;

	//line.clear();
	//line<<buf;
	//cout<<RED<<low<<RESET;
	while (abstract.good()) {
		abstract>>word;
		count++;
		if (count>=low){
			if (is_key(word)) {
				cout<<" "<<YELLOW<<word<<RESET;
			}
			else {
				cout<<" "<<word;
			}
			if ((count-high)> MAX_LEN/3 ){
				cout<<"...";
				break;
			}
		}
		word.clear();
	}
	cout<<"\n\n";
}

void load_link() {
	clock_t c_start = clock();
	ifstream fin;
	fin.open(LINKNAME);
	if (!fin.is_open()) {
		cerr<<"Not open."<<endl;
		return;
	}
	int NR_art = 0;
	while (!fin.eof()) {
        NR_art++;
		string buf, temp;
		int number, nr_link;
        getline(fin, buf);
		sscanf(buf.c_str(), "##%d:%d:", &number, &nr_link);
		//cout<<a<<" "<<b<<" "<<endl;
		int pos = buf.find_last_of(':');
		temp = buf.substr(pos+1);
		link_insert(number, nr_link, temp);
		//cout<<temp<<endl;

	}

	fin.close();
	clock_t c_end = clock();
	double cost_time = 1.0 * (c_end-c_start) / CLOCKS_PER_SEC;
	//cout<<"( "<<cost_time<< " seconds)\n";
	//cout<<endl;
}

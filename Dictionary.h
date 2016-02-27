#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <sstream>
using namespace std;

struct Doc{
    int docnum;
	int pos;
	int type;
    int weight;
	//Doc* next;
    //string title;
    //string abstract;

};
typedef vector <Doc> DOCS;
struct Node{
    string word;
    int	count;
	//Doc* doc;
	//Doc* tail;
	DOCS doc;
    //void insert(string);
};

struct Rela{
    int weight;
    vector <int> list;
};

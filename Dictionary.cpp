#include <iostream>
//#include <string>
#include <assert.h>

#include "Dictionary.h"
//using namespace std;



long transform_time=0;
long insert_time=0;
map <string, Node> dict;
set <string> exclude = {"the", "of", "and", "a", "to", "in", "is", "for", "that", "are", "with"};
vector <Rela> rela;
string transform(string word) {
	//clock_t c_start = clock();
    for (int i=0; i<word.length();i++){     //fliter invalid characters
        if (!(	(word[i]>='a' && word[i]<='z')
        	||	(word[i]>='A' && word[i]<='Z')
			||	(word[i]>='0' && word[i]<='9')
            || 	(i!=0 && word[i]=='-')        )) {
            word.erase(i,1);
            i--;
        }
    }
	if (word[0]>='a' && word[0]<='z') return word;
    string key="";                          //upper chars to lower
    int i=0;
    while (i<word.length()) {
		key+=tolower(word[i]);
    	i++;
    }
	//clock_t c_end = clock();
	//transform_time += c_end - c_start;
    return key;
}
void dict_insert(string word, int docnum, int type, int pos) {
    /*Doc content;
    content.no=no;
    content.title=title;
    content.abstract=abstract;*/

    //cout<<word<<"---";
    string key = transform(word);
	if (key.length() == 0) return;

	//clock_t c_start = clock();
    if (dict.find(key) == dict.end()) {          //Not exist
        //dict[key].word = word;
        dict[key].count = 1;
		//dict[key].doc = NULL;
    }
    else {                                      //Already in
        dict[key].count++;
    }

	//if (exclude.find(key) != exclude.end()) return;	//fliter the meaningless word


	//Doc* p = dict[key].tail;
	if (!dict[key].doc.empty() && dict[key].doc.back().docnum == docnum) return;
	Doc CurDoc;						//Link word to documents
	CurDoc.docnum = docnum;
	CurDoc.type = type;
	CurDoc.pos = pos;
    //cout<<weights[docnum-1]<<endl;
    CurDoc.weight = rela[docnum-1].weight;
	//CurDoc->next = NULL;
	dict[key].doc.push_back(CurDoc);
	/*if (p == NULL) {
		dict[key].doc = CurDoc;
		dict[key].tail = dict[key].doc;
	}
	else {
		dict[key].tail->next = CurDoc;
		dict[key].tail = CurDoc;
	}*/
	//clock_t c_end = clock();
	//insert_time += c_end - c_start;

    //dict.insert(pair<string, Node>);
}

void dict_print_all() {

    /*for (const auto &w : dict) {
		cout<< w.first << "\t\t"<< w.second.count<<" times"<<endl;
    }*/
	//cout<<"time in transform:"<< 1.0 * transform_time / CLOCKS_PER_SEC<<endl;
	//cout<<"time in insert	:"<< 1.0 * insert_time / CLOCKS_PER_SEC<<endl;
    cout<<"Dictionary contains "<<dict.size()<<" elements.\n";

}

void link_insert(int number, int nr_link, string content) {
    Rela p;
    p.weight = nr_link;
    ///weights.push_back(nr_link);
    stringstream list;
    list<<content;
    while (list.good()) {
        int num;
        list>>num;
        p.list.push_back(num);
    }
    rela.push_back(p);
}

#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <array>
using namespace std;

// const int multi = 53, add = 97;
const int multi = 553, add = 97;

/* Struct */
const int NLINE = 41929539;
// const int NHASH = 500000003;		// prime number
const int NHASH = 41929540;		// prime number

struct DIC {
	unsigned key;
	string str;
	unsigned freq;
};
DIC dictable[NLINE];
struct HASH_DIC {
	string str;
	unsigned freq;
};/*
list<HASH_DIC> hash_dic[NHASH];

inline void table2hash()
{
	for(int i = 0; i < NLINE; ++i) {
		hash_dic[ dictable[i].key ].push_back
				( (HASH_DIC){dictable[i].str, dictable[i].freq} );
	}
}
*/
/* Hash */
typedef unsigned hash_type;
hash_type hash_function(string *str)
{
	hash_type ret = 0;
	for(string::iterator i = str->begin(); i != str->end(); ++i)
		ret += ret * multi + *i - 'a' + add;		// notice the multiplier && adder
	ret %= NHASH;
	return ret;
}

/* Judge *//*
bool judge(string *str)
{
	hash_type key = hash_function(str);
	for(list<DIC>::iterator i = hash_dic[key].begin(); i != hash_dic[key].end(); ++i)
		if(*str == i->str)
			return 1;
	return 0;
}
*/

/* INPUT
string prep[20] = {"at", "by", "in", "of", "on"
				 , "to", "up", "for", "down", "from"
				 , "near", "than", "with", "about", "after"
				 , "since", "under", "before", "between", "without"};
inline bool isprep(string *str)
{
	for(int i = 0; i < 20; ++i)
		if(*str == prep[i])
			return 1;
	return 0;
}
inline void input_test()
{
	char c = 'a';
	while(c != EOF)
	{
		string str[50];
		bool prep[50];
		cin >> str[0];
		prep[0] = isprep(str);
		string allstr(str[0]);
		int nword;
		for(nword = 1; (c = getchar()) != EOF && c != '\n'; ++nword) {
			cin >> str[nword];
			prep[nword] = isprep(str + nword);
			allstr += ' ' + str[nword];
		}
		if(nword > 9) {
			cout << "query: " << allstr << '\n' << "output: 0\n" ;
		} else if(!nword) {		// no prep
			cout << "query: " << allstr << '\n' << "output: " ;
			
			cout << '\n';
		} else {
			cout << "query: " << allstr << '\n' << "output: " ;
			
			cout << '\n';
		} 
	}
	return ;
}
*/
int main(int argc, char *argv[])
{
	/* Input */
	char input[256];
	strcpy(input, argv[1]);
	for(int i = 2; i < argc; ++i)
		strcat(input, argv[i]);
	puts(input);
	
	FILE *fp = fopen(input, "rb");
	fread(dictable, sizeof(DIC), NLINE, fp);
	fclose(fp);
	
	cout << dictable[1].str << endl;		// DEBUG
	
	puts("==FINISH PRE==");
	
	// table2hash();
	
	puts("==FINISH BUILD HASH==");
	
	// input_test();

	puts("==FINISH==");
	
	return 0;
}

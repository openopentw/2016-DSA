#include <cstdio>
#include <iostream>
using std::cin;	using std::cout;
#include <string>
using std::string;

string prep[20] = {"at", "by", "in", "of", "on"
				 , "to", "up", "for", "down", "from"
				 , "near", "than", "with", "about", "after"
				 , "since", "under", "before", "between", "without"};
// prep_len: 2[0 ~ 6], 3[7], 4[8 ~ 12], 5[13 ~ 16], 6[17], 7[18 ~ 19]
struct TRIE {
	TRIE *next[27];
	unsigned freq;	// notice here
	bool isend;
} trie;
inline int make_index(char c) {
	return (c == ' ')? 26 : (c - 'a');
}

string *str_ptr;
string ans;

void lookup_correct()
{
	TRIE *root = &trie;
	for(int i = 0; i < str_ptr->size(); ++i) {
		int index = make_index((*str_ptr)[i]);
		if(root->next[index] == NULL) {
			cout << "NO!\n";
			break;
		} else {
			ans.push_back((*str_ptr)[i]);
		}
	}
}
void lookup_no_prep(int ED_level)
{
	
	return ;
}
inline void input()
{
	char c = 'a';
	while(c != EOF)
	{
		string str, tmp;
		cin >> str;
		while( (c = getchar()) != EOF && c != '\n' ) {
			cin >> tmp;
			str += ' ' + tmp;
		}
		
		cout << "query: " << str << '\n' << "output: " ;
		
		str_ptr = &str;
	}
	return ;
}
const unsigned long long NCHAR = 2000000000;	// 2: 167129901
inline void build_trie()
{
	char filename[] = "/tmp2/dsa2016_project/*gm.small.txt";
				//   01234567890123456789012
	char *buf = new char[NCHAR];
	for(char c = '2'; c < '6'; ++c)
	// for(char c = '2'; c < '3'; ++c)
	{
		filename[22] = c;	puts(filename);		// DEBUG
		FILE *fp = fopen(filename, "rb");
		while(int fend = fread(buf, sizeof(char), NCHAR, fp))
		{
			int last;
			for(last = 1; buf[fend - last] != '\n'; ++last)	;
			fseek(fp, -last + 1, SEEK_CUR);
			fend -= last;
			
			int end = 0;
			while(end < fend) {
				TRIE *curr = &trie;
				for(; buf[end] != '\t'; ++end) {
					int index = make_index(buf[end]);
					if(curr->next[index] == NULL)
						curr->next[index] = new TRIE;
					curr = curr->next[index];
				}
				++end;	// buf[end] == '\t'
				
				curr->isend = 1;
				for(; buf[end] != '\n'; ++end)
					curr->freq = curr->freq * 10 + buf[end] - '0';
				++end;	// buf[end] == '\n'
			}
		}
		fclose(fp);
	}
	delete [] buf;
	return ;
}
void release(TRIE *root)
{
	for(int i = 0; i < 27; ++i)
		if(root->next[i] != NULL)
			release(root->next[i]);
	delete root;
	return;
}
int main()
{
	build_trie();
	puts("==FINISH==");
	// string str("in the apple");
	// lookup_correct();
	// input();
	// release();
	return 0;
}

#include <cstdio>
#include <iostream>
using std::cin;	using std::cout;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <algorithm>
using std::sort;	using std::unique;

struct TRIE {
	string str;
	int freq;
	int len;	// lenth of word
	bool isend;	// this is the end of a sentence
	TRIE *next[28];		// notice here
};
TRIE root;
struct WFREQ {
	string str;
	int freq;
	bool operator<(WFREQ other) {
		return str < other.str;
	}
	bool operator==(WFREQ other) {
		return str == other.str;
	}
};
vector<WFREQ> wfreq;

// 'a' -> 'p' -> 'p' -> 'l' -> 'e' : 'isend'

inline int make_index(char c) {
	return c == ' '? 26 : (c - 'a');
}

/* Travel */
bool travel_correct(TRIE *root, const string &str, int pos)
{
	if(str.size() == pos)
		if(root->isend) {
			cout << "OK\n";
			return 1;
		} else {
			return 0;
		}
	int index = make_index(str[pos]);
	if(root->next[index] != NULL)
		return travel_correct(root->next[index], str, pos + 1);
	return 0;
}

vector<WFREQ> ans;
string *str_ref;
string prep[20] = {"at", "by", "in", "of", "on", "to", "up", "for", "down", "from", "near", "than", "with", "about", "after", "since", "under", "before", "between", "without"};
// notice: "at by" or "at", "by"
inline int find_next_space(int pos) {
	for(++pos; pos < str_ref->size() && (*str_ref)[pos] != ' '; ++pos)	;
	return pos;
}
void travel_ED(TRIE* root, int pos, int ED_level)
{
	if(root->isend && str_ref->size() == pos) {
		ans.push_back((WFREQ){root->str, root->freq});
		if(!ED_level)	return;
	}
	int index;
	if(pos < str_ref->size())
		index = make_index((*str_ref)[pos]);
	if(pos < str_ref->size() && root->next[index] != NULL)
		travel_ED(root->next[index], pos + 1, ED_level);
	if(ED_level)
	{
		/* insert */
		// for(char c = 'a'; c <= 'z'; ++c)
			// if(root->next[c + 64] != NULL)
				// travel_ED(root->next[c + 64, pos, ED_level - 1);
		// if(root->next[26] != NULL && (*str_ref)[pos] == ' ')	// can be combined with part of delete
		// {
			// for(int i = 0; i < 19; ++i) {
				// TRIE *curr = root->next[26];
				// for(int j = 0; j < prep[i].size() && curr->next[prep[i]] != NULL; ++j)
					// curr = curr->next[prep[i]];
			// }
		// }
		/* delete */
		if(!pos)
			travel_ED(root, find_next_space(pos) + 1, ED_level - 1);
		if((root->next[26] != NULL || root->isend) && (*str_ref)[pos] == ' ')
			travel_ED(root, find_next_space(pos), ED_level - 1);
		/* substitute */
		// for(char c = 'a'; c <= 'z'; ++c)
			// if(root->next[c + 64] != NULL && c != (*str_ref)[pos])
				// travel_ED(root->next[c + 64], pos + 1, ED_level - 1);
	}
}

/* Input Test Data */
void input_test()
{
	char c;
	while(c != EOF)
	{
		string str, tmp;
		cin >> str;
		while( (c = getchar()) != EOF && c != '\n') {
			cin >> tmp;
			str += ' ' + tmp;
			// cout << str;
		}
		
		cout << "query: " << str << '\n'
			 << "output: " ;
		if(!travel_correct(&root, str, 0)) {
			str_ref = &str;
			travel_ED(&root, 0, 2);
			if(!ans.empty()) {
				sort(ans.begin(), ans.end());
				vector<WFREQ>::iterator it = unique(ans.begin(), ans.end());
				ans.erase(it, ans.end());
				cout << ans.size() << '\n';
				for(vector<WFREQ>::iterator i = ans.begin(); i != ans.end(); ++i)
					cout << i->str << '\t' << i->freq << '\n';
				ans.clear();
			} else {
				cout << "NONE\n";
			}
		}
	}
	return ;
}

/* Input Dic Data */
const unsigned long long NCHAR = 2000000000;	// 2: 167129901
// const unsigned long long NCHAR = 10000000000;	// 2: 167129901
							//	   167129901
void input_dic()
{
	char *buf = new char[NCHAR];
	// char fname[] = "/tmp2/handsomeP/2gm.small.txt";
				//  01234567890123456
	char fname[] = "/tmp2/dsa2016_project/2gm.small.txt";
				//  01234567890123456789012
	FILE *fp;
	// for(char i = '2'; i < '6'; ++i)
	for(char i = '5'; i < '6'; ++i)
	{
		fname[22] = i;
		puts(fname);		// DEBUG
		fp = fopen(fname, "rb");
		while(int fend = fread(buf, sizeof(char), NCHAR, fp))
		{
			int last;
			for(last = 1; buf[fend - last] != '\n'; ++last)	;
			fseek(fp, -last + 1, SEEK_CUR);
			
			int end = 0;
			while(end < fend) {
				TRIE *curr = &root;
				int beg = end;
				for(;end < fend && buf[end] != '\t'; ++end) {
					// int index = make_index(buf[end]);
					if(buf[end] == ' ') {
						
					}
					int index = buf[end] - 'a';
					if(curr->next[index] == NULL) {
						TRIE *next = new TRIE;
						curr->next[index] = next;
						curr = next;
					} else {
						curr = curr->next[index];
					}
				}
				++end;	// buf[end] == '\t'
				curr->str.assign(buf + beg, buf + end);
				curr->isend = 1;
				for(;end < fend && buf[end] != '\n'; ++end)
					curr->freq = curr->freq * 10 + buf[end] - '0';
				++end;	// buf[end] == '\n'
			}
		}
	}
	fclose(fp);
	delete [] buf;
}
void free(TRIE *root)
{
	for(int i = 0; i < 28; ++i)
		if(root->next[i] != NULL) {
			for(int j = 0; j < 28; ++j)
				if(root->next[i]->next[j] != NULL)
					free(root->next[i]);
			delete root->next[i];
			root->next[i] = NULL;
		}
}
int main()
{
	input_dic();
	// puts("");
	// input_test();
	// free(&root);	// time 差 40s 左右 /
	return 0;
}

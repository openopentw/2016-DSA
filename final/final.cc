#include <cstdio>
#include <iostream>
using std::cin;	using std::cout;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <algorithm>
using std::sort;	using std::unique;

string prep[20] = {"at", "by", "in", "of", "on"
				 , "to", "up", "for", "down", "from"
				 , "near", "than", "with", "about", "after"
				 , "since", "under", "before", "between", "without"};

struct TRIE {
	TRIE *next[27];
	string str;
	unsigned freq;	// notice here
	bool isend;
} trie;
inline int make_index(char c) {
	return (c == ' ')? 26 : (c - 'a');
}

struct ANS {
	string str;
	unsigned freq;
};
vector<ANS> ans;
bool cmp (const ANS &a, const ANS &b) {
	if(a.freq == b.freq)
		return a.str < b.str;
	return a.freq > b.freq;
}
bool cmp_uniq (const ANS &a, const ANS &b) {
	return (a.str == b.str);
}

string str_ptr;
string str_part[50];
bool isprep[50];
int nword;

void lookup_correct(TRIE *root, int step)
{
	if(step == str_ptr.size()) {
		if(root->isend)
			ans.push_back( (ANS){str_ptr, root->freq} );
		return ;
	}
	int index = make_index(str_ptr[step]);
	if(root->next[index] == NULL)	return;
	lookup_correct(root->next[index], step + 1);
}

void lookup_no_prep_1()
{
	for(int i = 0; i < nword + 1; ++i)
		for(int k = 0; k < 20; ++k)
		{
			int m = 0;
			for( ; m < i; ++m) {
				if(!m) {
					str_ptr = str_part[m];
				} else {
					str_ptr += ' ' + str_part[m];
				}
			}
			if(!m) {
				str_ptr = prep[k];
			} else {
				str_ptr += ' ' + prep[k];
			}
			
			for( ; m < nword; ++m)
				str_ptr += ' ' + str_part[m];
			
			// cout << str_ptr << '\n';		// DEBUG
			
			lookup_correct(&trie, 0);
		}
}
void lookup_no_prep_2()
{
	for(int i = 0; i < nword + 1; ++i)
	for(int j = i; j < nword + 1; ++j)
		for(int k = 0; k < 20; ++k)
		for(int l = 0; l < 20; ++l)
		{
			int m = 0;
			for( ; m < i; ++m) {
				if(!m) {
					str_ptr = str_part[m];
				} else {
					str_ptr += ' ' + str_part[m];
				}
			}
			if(!m) {
				str_ptr = prep[k];
			} else {
				str_ptr += ' ' + prep[k];
			}
			
			for( ; m < j; ++m)
				str_ptr += ' ' + str_part[m];
			str_ptr += ' ' + prep[l];
			
			for( ; m < nword; ++m)
				str_ptr += ' ' + str_part[m];
			
			// cout << str_ptr << '\n';		// DEBUG
			
			lookup_correct(&trie, 0);
		}
}

inline bool judge_prep(string *str)
{
	for(int i = 0; i < 20; ++i)
		if(*str == prep[i])
			return 1;
	return 0;
}
void special(int end)
{
	for( ; end < nword && !(isprep[end]); ++end) {		// to find the first prep
		// if(!end) {
		if(str_ptr.empty()) {
			str_ptr = str_part[end];
		} else {
			str_ptr += ' ' + str_part[end];
		}
	}
	if(end == nword) {
		lookup_correct(&trie, 0);
		return ;
	}
	string old(str_ptr);
	int beg = end;
	
	for( ; end < nword && isprep[end]; ++end) {		// to find the last prep
		if(str_ptr.empty()) {
			str_ptr = str_part[end];
		} else {
			str_ptr += ' ' + str_part[end];
		}
	}
	
	/* Nothing */
	if(end == nword) {
		lookup_correct(&trie, 0);
	} else {
		special(end);
	}
	
	/* Insert */		// BUG HERE!!!
	for(int i = beg; i < end + 1; ++i)
		for(int k = 0; k < 20; ++k)
		{
			str_ptr = old;
			int m = beg;
			for( ; m < i; ++m) {
				if(str_ptr.empty()) {
					str_ptr = str_part[m];
				} else {
					str_ptr += ' ' + str_part[m];
				}
			}
			
			if(str_ptr.empty()) {
				str_ptr = prep[k];
			} else {
				str_ptr += ' ' + prep[k];
			}
			
			for( ; m < end; ++m)
				str_ptr += ' ' + str_part[m];
			
			if(end == nword) {
				lookup_correct(&trie, 0);
			} else {
				special(end);
			}
		}
	
	/* Delete */
	for(int i = beg; i < end; ++i) {
		str_ptr = old;
		int m = beg;
		for( ; m < i; ++m) {
			if(str_ptr.empty()) {
				str_ptr.clear();
				str_ptr = str_part[m];
			} else {
				str_ptr += ' ' + str_part[m];
			}
		}
		++m;
		for( ; m < end; ++m)
			if(str_ptr.empty()) {
				str_ptr.clear();
				str_ptr = str_part[m];
			} else {
				str_ptr += ' ' + str_part[m];
			}
		
		if(end == nword) {
			lookup_correct(&trie, 0);
		} else {
			special(end);
		}
	}
	/* Substitute */
	for(int i = beg; i < end + 1; ++i)
		for(int k = 0; k < 20; ++k)
		{
			str_ptr = old;
			int m = beg;
			for( ; m < i; ++m) {
				if(str_ptr.empty()) {
					str_ptr = str_part[m];
				} else {
					str_ptr += ' ' + str_part[m];
				}
			}
			
			if(str_ptr.empty()) {
				str_ptr = prep[k];
			} else {
				str_ptr += ' ' + prep[k];
			}
			
			++m;
			for( ; m < end; ++m)
				str_ptr += ' ' + str_part[m];
			
			if(end == nword) {
				lookup_correct(&trie, 0);
			} else {
				special(end);
			}
		}
}

inline bool exist_prep()
{
	for(int i = 0; i < nword; ++i)
		if(isprep[i])
			return 1;
	return 0;
}
inline void input()
{
	char c = 'a';
	while(c != EOF)
	{
		/* 分析 prep */
		if(!(cin >> str_part[0]))	break;
		isprep[0] = judge_prep(str_part);
		str_ptr.assign(str_part[0]);
		for(nword = 1; (c = getchar()) != EOF && c != '\n'; ++nword) {
			cin >> str_part[nword];
			isprep[nword] = judge_prep(str_part + nword);
			str_ptr += ' ' + str_part[nword];
		}
		
		/* output */
		cout << "query: " << str_ptr << '\n' << "output: " ;
		
		if(nword > 9) {
			cout << "0\n";
			continue;
		}
		
		lookup_correct(&trie, 0);
		
		if(!exist_prep()) {		// no prep
			lookup_no_prep_1();
			lookup_no_prep_2();
		} else {
			str_ptr.clear();
			special(0);
		}
		
		sort(ans.begin(), ans.end(), cmp);
		vector<ANS>::iterator uend = unique(ans.begin(), ans.end(), cmp_uniq);
		ans.erase(uend, ans.end());
		
		int min = (ans.size() < 10)? ans.size() : 10;
		cout << min << '\n';
		for(int i = 0; i < min; ++i)
			cout << ans[i].str << '\t' << ans[i].freq << '\n';
		
		ans.clear();
	}
	return ;
}

const unsigned long long NCHAR = 200000000;	// 2: 167129901
inline void build_trie()
{
	char filename[] = "/tmp2/dsa2016_project/*gm.small.txt";
				//   01234567890123456789012
	char *buf = new char[NCHAR];
	for(char c = '2'; c < '6'; ++c)
	// for(char c = '3'; c < '4'; ++c)
	{
		filename[22] = c;	//	puts(filename);		// DEBUG
		FILE *fp = fopen(filename, "rb");
		while(int fend = fread(buf, sizeof(char), NCHAR, fp))
		{
			int last;
			for(last = 1; buf[fend - last] != '\n'; ++last)	;
			fseek(fp, -last + 1, SEEK_CUR);
			fend -= last;
			
			int end = 0;
			while(end < fend) {
				int beg = end;
				
				TRIE *curr = &trie;
				for(; buf[end] != '\t'; ++end) {
					int index = make_index(buf[end]);
					if(curr->next[index] == NULL)
						curr->next[index] = new TRIE;
					curr = curr->next[index];
				}
				++end;	// buf[end] == '\t'
				
				curr->str.assign(buf + beg, buf + end);
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
	// puts("==FINISH==");
	input();
	// release();
	return 0;
}

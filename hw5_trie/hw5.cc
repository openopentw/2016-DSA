#include <cstdio>
#include <iostream>
using std::cin;	using std::cout;	using std::endl;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <algorithm>
using std::sort;	using std::unique;

const int NCHAR = 4194304;	// 3716714
const int MINUS = 55;
const int NLINE = 133910 - MINUS;

struct TRIE {
	string str;
	bool isend = 0;
	TRIE *next[200] = {NULL};
};
TRIE root;

// next[char + 64]
// 'a' 'p' 'p' 'l' 'e' 'isend'

/* Travel */
string *str_ref;
bool travel_correct(TRIE *root, int pos)
{
	if(str_ref->size() == pos && root->isend) {
		cout << " OK\n";
		return 1;
	}
	if(root->next[(*str_ref)[pos] + 64] != NULL)
		return travel_correct(root->next[(*str_ref)[pos] + 64], pos + 1);
	return 0;
}
vector<string> ans;
void travel_ED(TRIE* root, int pos, int ED_level)
{
	if(root->isend && str_ref->size() == pos) {
		ans.push_back(root->str);
		if(!ED_level)	return;
	}
	if(root->next[(*str_ref)[pos] + 64] != NULL)
		travel_ED(root->next[(*str_ref)[pos] + 64], pos + 1, ED_level);
	if(ED_level)
	{
		/* insert */
		for(char c = 'a'; c <= 'z'; ++c)
			if(root->next[c + 64] != NULL)
				travel_ED(root->next[c + 64], pos, ED_level - 1);
		/* delete */
		travel_ED(root, pos + 1, ED_level - 1);
		/* substitute */
		for(char c = 'a'; c <= 'z'; ++c)
			if(root->next[c + 64] != NULL && c != (*str_ref)[pos])
				travel_ED(root->next[c + 64], pos + 1, ED_level - 1);
		/* transpose */
		if(root->next[(*str_ref)[pos + 1] + 64] != NULL)
			if(root->next[(*str_ref)[pos + 1] + 64]->next[(*str_ref)[pos] + 64] != NULL)
				travel_ED(root->next[(*str_ref)[pos + 1] + 64]->next[(*str_ref)[pos] + 64]
															, pos + 2, ED_level - 1);
		if(ED_level == 2) {
			/* transpose && insert */
			for(char c = 'a'; c <= 'z'; ++c)
				if(root->next[(*str_ref)[pos + 1] + 64] != NULL)
				if(root->next[(*str_ref)[pos + 1] + 64]->next[c + 64] != NULL)
				if(root->next[(*str_ref)[pos + 1] + 64]->next[c + 64]->next[(*str_ref)[pos] + 64] != NULL)
					travel_ED(root->next[(*str_ref)[pos + 1] + 64]->next[c + 64]->next[(*str_ref)[pos] + 64]
															, pos + 2, ED_level - 2);
			// /* delete && transpose */
			if(pos < str_ref->size())
				if(root->next[(*str_ref)[pos + 2] + 64] != NULL)
				if(root->next[(*str_ref)[pos + 2] + 64]->next[(*str_ref)[pos] + 64] != NULL)
					travel_ED(root->next[(*str_ref)[pos + 2] + 64]->next[(*str_ref)[pos] + 64]
															, pos + 3, ED_level - 2);
		}
	}
}

/* Input Dic Data */
char in_dic[NCHAR];
void input_dic()
{
	FILE *fp = fopen("/tmp2/dsa2016_hw5/cmudict-0.7b", "rb");
	int inend = fread(in_dic, sizeof(char), NCHAR, fp);
	fclose(fp);
	// printf("%d\n", inend);
	
	int line;
	char *end;
	for(line = 0, end = in_dic; line < MINUS; ++end, ++line)
		while(*end != '\n')	++end;
	
	for(; end < in_dic + inend; ++end) {
		char *beg = end;
		
		TRIE *curr = &root;
		while(end < in_dic + inend && *end != ' ' && *end != '\n') {
			if('A' <= *end && *end <= 'Z')	*end += 32;
			
			/* build trie tree */
			if(curr->next[*end + 64] == NULL) {
				TRIE *next = new TRIE;
				curr->next[*end + 64] = next;
			}
			curr = curr->next[*end + 64];
			
			// if(curr->next[*end + 64] != NULL) {
				// curr = curr->next[*end + 64];
			// } else {	// node doesn't exist
				// TRIE *next = new TRIE;
				// curr->next[*end + 64] = next;
				// curr = next;
			// }
			
			++end;
		}
		curr->str.assign(beg, end);
		curr->isend = 1;
		
		while(end < in_dic + inend && *end != '\n')
			++end;
	}
}

/* Input Test Data */
char in_test[NCHAR + 1];
void input_test()
{
	int inend = fread(in_test, sizeof(char), NCHAR, stdin);
	if(in_test[inend - 1] != '\n')
		in_test[inend++] = '\n';
	// cout << inend << endl;
	for(char *end = in_test; end < in_test + inend; ++end) {
		char *beg = end;
		// while(end < in_dic + inend && *end != ' ' && *end != '\t' && *end != '\n') {
		while(end < in_dic + inend && *end != '\t' && *end != '\n') {
			++end;
		}
		
		string str(beg, end);
		str_ref = &str;
		
		cout << str << " ==>";
		
		if(!travel_correct(&root, 0)) {
			travel_ED(&root, 0, 2);
			if(!ans.empty()) {
				sort(ans.begin(), ans.end());
				vector<string>::iterator it = unique(ans.begin(), ans.end());
				ans.erase(it, ans.end());
				for(vector<string>::iterator i = ans.begin(); i != ans.end(); ++i)
					cout << ' ' << *i;
				cout << '\n';
				// cout << ans.size() << '\n';
				ans.clear();
			} else {
				cout << " NONE\n";
			}
		}
		
		while(end < in_dic + inend && *end != '\n')
			++end;
	}
	return;
}

int main()
{
	std::ios::sync_with_stdio(false);
	cout.tie(0);
	input_dic();
	input_test();
	return 0;
}

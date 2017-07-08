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

/* Input Dic Data */
vector<char> count;
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
		while(end < in_dic + inend && *end != ' ' && *end != '\n') {
			if('A' <= *end && *end <= 'Z')	*end += 32;
			count.push_back(*end);
			++end;
		}
		
		while(end < in_dic + inend && *end != '\n')
			++end;
	}
	sort(count.begin(), count.end());
	vector<char>::iterator it = unique(count.begin(), count.end());
	count.erase(it, count.end());
}

int main()
{
	std::ios::sync_with_stdio(false);
	cout.tie(0);
	input_dic();
	for(vector<char>::iterator i = count.begin(); i != count.end(); ++i)
		cout << *i << endl << *i - 0 << endl;
	cout << "\\0" << endl << '\0' - 0 << endl;
	return 0;
}

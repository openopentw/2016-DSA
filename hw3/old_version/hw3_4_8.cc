#include <cstdio>	// fopen
#include <cctype>	// isdigit
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <algorithm>
using std::distance;

struct LINE {
	vector<int> line;
	int len;	// m or n
	int min, max;
};

/*
 *	' ' -> not filled yet
 *	'#' -> O (#)
 *	'.' -> X (.)
 */

int m, n;
vector<LINE> row;	// 橫的那一排 /
vector<LINE> col;	// 直的那一排 /
char map[32][32];	// 從 [1][1] 開始填 /
bool row_change[32], col_change[32];

/* code start */

void fill_row()
{
	for(vector<LINE>::iterator i = row.begin(); i != row.end(); ++i) {
		int row_n = distance(row.begin(), i) + 1;
		int len = 0;
		for(vector<int>::iterator j = i->line.begin(); j != i->line.end(); ++j)
			len += *j + 1;
		--len;
		
		int lack = n - len;
		int tmp = 1;	// tmp sum
		for(vector<int>::iterator j = i->line.begin(); j != i->line.end(); ++j) {
			for(int k = lack; k < *j; ++k) {	// it works only when (lack < *j)
				map[row_n][tmp + k] = '#';
				col_change[tmp + k] = 1;
			}
			if(!lack) {
				map[row_n][tmp + *j] = '.';
				col_change[tmp + *j] = 1;
			}
			tmp += *j + 1;
		}
	}
}
void fill_col()
{
	for(vector<LINE>::iterator i = col.begin(); i != col.end(); ++i) {
		int col_n = distance(col.begin(), i) + 1;
		int len = 0;
		for(vector<int>::iterator j = i->line.begin(); j != i->line.end(); ++j)
			len += *j + 1;
		--len;
		
		int lack = m - len;
		int tmp = 1;	// tmp sum
		for(vector<int>::iterator j = i->line.begin(); j != i->line.end(); ++j) {
			for(int k = lack; k < *j; ++k) {	// it works only when (lack < *j)
				map[tmp + k][col_n] = '#';
				row_change[tmp + k] = 1;
			}
			if(!lack) {
				map[tmp + *j][col_n] = '.';
				row_change[tmp + *j] = 1;
			}
			tmp += *j + 1;
		}
	}
	return;
}

char b[10000];		// notice the volume
void input()
{
	cin >> m >> n;	// 0 < m, n < 31	// 原本是101，變成31了...
	row.resize(m);
	col.resize(n);
	
	fread(b, sizeof(char), 10000, stdin);
	
	int i = 0;
	/* row */
	while(!isdigit(b[i])) {	++i;	}
	int tmp = b[i] - '0';	++i;
	vector<LINE>::iterator it = row.begin();
	while(it != row.end()) {
		if(isdigit(b[i])) {
			tmp = tmp * 10 + b[i] - '0';
			++i;
		} else {	// b[i] == '\n' or ' '
			if(tmp) {
				if(it->line.empty()) {
					it->min = it->max = tmp;
				} else {
					it->min = (tmp < it->min)? tmp : it->min;
					it->max = (tmp > it->max)? tmp : it->max;
				}
				it->line.push_back(tmp);
				tmp = 0;
			}
			if(b[i] == '\n') {
				++it;
				if(it == row.end())	break;
				it->len = n;
			}
			++i;
		}
	}
	/* col */
	while(!isdigit(b[i])) {	++i;	}
	tmp = b[i] - '0';	++i;
	it = col.begin();
	while(it != col.end()) {
		if(isdigit(b[i])) {
			tmp = tmp * 10 + b[i] - '0';
			++i;
		} else {	// b[i] == '\n' or ' '
			if(tmp) {
				if(it->line.empty()) {
					it->min = it->max = tmp;
				} else {
					it->min = (tmp < it->min)? tmp : it->min;
					it->max = (tmp > it->max)? tmp : it->max;
				}
				it->line.push_back(tmp);
				tmp = 0;
			}
			if(b[i] == '\n') {
				++it;
				if(it == col.end())	break;
				it->len = n;
			}
			++i;
		}
	}
	return;
}
void input_debug()		// DEBUG
{
	cout << "row" << endl;
	for(vector<LINE>::iterator i = row.begin(); i != row.end(); ++i) {
		for(vector<int>::iterator j = i->line.begin(); j != i->line.end(); ++j) {
			cout << *j << ' ';
		}
		cout << "end " << i->min << ' ' << i->max << endl;
	}
	cout << endl << "col" << endl;
	for(vector<LINE>::iterator i = col.begin(); i != col.end(); ++i) {
		for(vector<int>::iterator j = i->line.begin(); j != i->line.end(); ++j) {
			cout << *j << ' ';
		}
		cout << "end " << i->min << ' ' << i->max << endl;
	}
}
void printmap()
{
	cout << endl;
	for(int i = 0; i != n; ++i)	cout << (i + 1) % 10;
	cout << endl;
	for(int i = 0; i != n; ++i)	cout << '-';
	cout << '|' << endl;
	for(int i = 0; i != m; ++i) {
		fwrite(&(map[i + 1][1]), sizeof(char), n, stdout);
		putchar('|');
		cout << i + 1;
		putchar('\n');
	}
	for(int i = 0; i != n; ++i)	cout << '-';
	cout << '|'  << endl;
	return;
}
int main()
{
	input();
	// input_debug();
	fill_row();
	fill_col();
	printmap();
	return 0;
}

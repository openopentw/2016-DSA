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
	/* below may be 累贅 */
	int len;	// m or n
	int min, max;
};

typedef vector<LINE>::iterator VLit;
typedef vector<int>::iterator VIit;

/*
 *	' ' -> not filled yet
 *	'#' -> O (#)
 *	'.' -> X (.)
 */

int m, n;
vector<LINE> row;	// 橫的那一排 /
vector<LINE> col;	// 直的那一排 /
char map[32][32];
bool row_change[32], col_change[32];

/* code start */

void single_space_row(int row_n, VIit row_beg, int map_beg, int map_len, int map_cen_beg, int map_cen_end)
{
	int lack ;
}

void inter_row(int row_n, VIit row_beg, VIit row_end, int map_beg, int map_end)	// intersection(交集)
{
	int len = 0;		// 最短的長度 /
	for(VIit i = row_beg; i != row_end; ++i)
		len += 1 + *i;
	--len;
	
	int lack = map_end - map_beg - len;
	int tmp = map_beg;	// tmp sum
	for(VIit i = row_beg; i != row_end; ++i) {
		for(int j = lack; j < *i; ++j) {	// it works only when (lack < *i)
			map[row_n][tmp + j] = '#';
			row_change[tmp + j] = 1;
		}
		if(!lack) {
			map[row_n][tmp + *i] = '.';
			row_change[tmp + *i] = 1;
		}
		tmp += *i + 1;
	}
}
void inter_col(int col_n, VIit col_beg, VIit col_end, int map_beg, int map_end)
{
	int len = 0;
	for(VIit i = col_beg; i != col_end; ++i)
		len += 1 + *i;
	--len;
	
	int lack = map_end - map_beg - len;
	int tmp = map_beg;	// tmp sum
	for(VIit i = col_beg; i != col_end; ++i) {
		for(int j = lack; j < *i; ++j) {	// it works only when (lack < *i)
			map[tmp + j][col_n] = '#';
			col_change[tmp + j] = 1;
		}
		if(!lack) {
			map[tmp + *i][col_n] = '.';
			row_change[tmp + *i] = 1;
		}
		tmp += *i + 1;
	}
}
void init_fill()
{
	for(VLit i = row.begin(); i != row.end(); ++i)
		inter_row(distance(row.begin(), i), i->line.begin(), i->line.end(), 0, n);
	for(VLit i = col.begin(); i != col.end(); ++i)
		inter_col(distance(col.begin(), i), i->line.begin(), i->line.end(), 0, m);
	return;
}

char b[10000];		// notice the volume
void input()
{
	scanf("%d%d", &m, &n);	// 0 < m, n < 31	// 原本是101，變成31了...
	row.resize(m);
	col.resize(n);
	
	fread(b, sizeof(char), 10000, stdin);
	
	int i = 0;
	/* row */
	while(!isdigit(b[i])) {	++i;	}
	int tmp = b[i] - '0';	++i;
	VLit it = row.begin();
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
	for(VLit i = row.begin(); i != row.end(); ++i) {
		for(VIit j = i->line.begin(); j != i->line.end(); ++j) {
			cout << *j << ' ';
		}
		cout << "end " << i->min << ' ' << i->max << endl;
	}
	cout << endl << "col" << endl;
	for(VLit i = col.begin(); i != col.end(); ++i) {
		for(VIit j = i->line.begin(); j != i->line.end(); ++j) {
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
		fwrite(&(map[i][0]), sizeof(char), n, stdout);
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
	init_fill();
	printmap();
	return 0;
}

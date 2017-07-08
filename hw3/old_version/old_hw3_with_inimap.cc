#include <cstdio>
#include <cctype>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <vector>
using std::vector;

struct LINE {
	vector<int> line;	// 改成 array
	int len;	// all '#'
	int fin;	// finish
	/* below may be 累贅 */
	int min, max;
};

typedef vector<LINE>::iterator VLit;
typedef vector<int>::iterator VIit;

/*
 *	' ' -> not filled yet
 *	'#' -> O (#)
 *	'.' -> X (.)
 */

vector<LINE> row;	// 橫的那一排 /
vector<LINE> col;	// 直的那一排 /
int row_n, col_n;	// number of row / col
char map[32][32];	// map[row_th][col_th]
char inimap[32][32];
bool row_change[32], col_change[32];

/* functions part */

void full_row(int row_th)
{
	int Olen = 0, Xlen = 0;
	for(int i = 0; i < col_n; ++i)
		if(inimap[row_th][i] == '#')
			++Olen;
	if(Olen == row[row_th].len) {
		row[row_th].fin = 1;
		for(int i = 0; i < col_n; ++i)
			if(inimap[row_th][i] != '#')
				inimap[row_th][i] = '.';
	}
}
void full_col(int col_th)
{
	int Olen = 0, Xlen = 0;
	for(int i = 0; i < row_n; ++i)
		if(inimap[i][col_th] == '#')
			++Olen;
	if(Olen == col[col_th].len) {
		col[col_th].fin = 1;
		for(int i = 0; i < row_n; ++i)
			if(inimap[i][col_th] != '#')
				inimap[i][col_th] = '.';
	}
}

void single_in_row(int row_th, int row_len, int map_cen_beg, int map_cen_end)
{
	if(map_cen_end - map_cen_beg <= row_len)
		for(int i = map_cen_beg; i < map_cen_end; ++i)
			inimap[row_th][i] = '#';
}
void single_in_col(int col_th, int col_len, int map_cen_beg, int map_cen_end)
{
	if(map_cen_end - map_cen_beg <= col_len)
		for(int i = map_cen_beg; i < map_cen_end; ++i)
			inimap[i][col_th] = '#';
}

void single_out_row(int row_th, int row_len, int map_beg, int map_end, int map_cen_beg, int map_cen_end)
// including rim_check
{
	int tmp = map_end - row_len;
	if(tmp < map_cen_beg)
		for(int i = tmp; i < map_cen_beg; ++i)		// notice here
			inimap[row_th][i] = '#';
	
	tmp = map_beg + row_len;
	if(tmp > map_cen_end)
		for(int i = map_cen_beg; i < tmp; ++i)
			inimap[row_th][i] = '#';
	
	tmp = map_cen_beg + row_len;
	if(tmp < map_end)
		inimap[row_th][tmp] = '.';
	
	tmp = map_cen_end - row_len - 1;
	if(tmp >=map_beg)
		inimap[row_th][tmp] = '.';
}
void single_out_col(int col_th, int col_len, int map_beg, int map_end, int map_cen_beg, int map_cen_end)
// including rim_check
{
	int tmp = map_end - col_len;
	if(tmp < map_cen_beg)
		for(int i = tmp; i < map_cen_beg; ++i)		// notice here
			inimap[i][col_th] = '#';
	
	tmp = map_beg + col_len;
	if(tmp > map_cen_end)
		for(int i = map_cen_beg; i < tmp; ++i)
			inimap[i][col_th] = '#';
	
	tmp = map_cen_beg + col_len;
	if(tmp < map_end)
		inimap[tmp][col_th] = '.';
	
	tmp = map_cen_end - col_len - 1;
	if(tmp >=map_beg)
		inimap[tmp][col_th] = '.';
}

void inter_row(int row_th, VIit row_beg, VIit row_end, int map_beg, int map_end)
{
	int len = 0;		// 最短的長度 /
	for(VIit i = row_beg; i != row_end; ++i)
		len += 1 + *i;
	--len;
	
	int lack = map_end - map_beg - len;
	int tmp = map_beg;	// tmp sum
	for(VIit i = row_beg; i != row_end; ++i) {
		for(int j = lack; j < *i; ++j) {	// it works only when (lack < *i)
			inimap[row_th][tmp + j] = '#';
			row_change[tmp + j] = 1;
		}
		if(!lack) {
			inimap[row_th][tmp + *i] = '.';
			row_change[tmp + *i] = 1;
		}
		tmp += *i + 1;
	}
}
void inter_col(int col_th, VIit col_beg, VIit col_end, int map_beg, int map_end)
{
	int len = 0;
	for(VIit i = col_beg; i != col_end; ++i)
		len += 1 + *i;
	--len;
	
	int lack = map_end - map_beg - len;
	int tmp = map_beg;	// tmp sum
	for(VIit i = col_beg; i != col_end; ++i) {
		for(int j = lack; j < *i; ++j) {	// it works only when (lack < *i)
			inimap[tmp + j][col_th] = '#';
			col_change[tmp + j] = 1;
		}
		if(!lack) {
			inimap[tmp + *i][col_th] = '.';
			row_change[tmp + *i] = 1;
		}
		tmp += *i + 1;
	}
}

// not finished
void parsing_row(int row_th, VIit row_beg, VIit row_end, int map_beg, int map_end)
{
	for(int i = map_beg; i < map_end; ++i)
		if(inimap[row_th][i] == '#') {
			int j;
			for(j = i + 1; j < map_end && inimap[row_th][j] != '.'; ++j) ;
			if(j - i == *row_beg) {
				for(int k = map_beg; k < i; ++k)
					inimap[row_th][k] = '.';
				inimap[row_th][j] = '.';
			}
		}
	for(int i = map_end; i > map_beg; --i)
		if(inimap[row_th][i] == '#') {
			int j;
			for(j = i - 1; j > map_beg && inimap[row_th][j] != '.'; --j) ;
			if(i - j == *row_end) {
				for(int k = map_end; k > i; --k)
					inimap[row_th][k] = '.';
				inimap[row_th][j] = '.';
			}
		}
	// parsing_row(row_th, row_beg + , row_end - , map_beg + , map_end - );
}

void init_fill()
{
	for(VLit i = row.begin(); i != row.end(); ++i) {
		int row_th = i - row.begin();
		inter_row(row_th, i->line.begin(), i->line.end(), 0, col_n);
		full_row(row_th);
	}
	for(VLit i = col.begin(); i != col.end(); ++i) {
		int col_th = i - col.begin();
		inter_col(col_th, i->line.begin(), i->line.end(), 0, row_n);
		full_col(col_th);
	}
	return;
}

/* recursive part */
int judge_whole_row(int row_th)
{
	int col_th = 0;
	for(VIit it = row[row_th].line.begin(); it != row[row_th].line.end(); ++it) {
		while(col_th < col_n && map[row_th][col_th] == '.')	++col_th;
		int len = 0;
		while(col_th < col_n && map[row_th][col_th] == '#')	++col_th, ++len;
		if(len != *it)	return 0;
	}
	for( ; col_th < col_n; ++col_th)
		if(map[row_th][col_th] == '#')
			return 0;
	return 1;
}
int judge_whole_col(int col_th)
{
	int row_th = 0;
	for(VIit it = col[col_th].line.begin(); it != col[col_th].line.end(); ++it) {
		while(row_th < row_n && map[row_th][col_th] == '.')	++row_th;
		int len = 0;
		while(row_th < row_n && map[row_th][col_th] == '#')	++row_th, ++len;
		if(len != *it)	return 0;
	}
	for( ; row_th < row_n; ++row_th)
		if(map[row_th][col_th] == '#')
			return 0;
	return 1;
}

void printmap_debug();	// DEBUG

int judge_row(int row_th, int col_end)
{
	int col_th = 0;
	for(VIit it = row[row_th].line.begin(); it != row[row_th].line.end(); ++it) {
		while(col_th < col_end && map[row_th][col_th] == '.')	++col_th;
		if(col_th == col_end)
			return 1;
		int len = 0;
		while(col_th < col_end && map[row_th][col_th] == '#')	++col_th, ++len;
		if(col_th == col_end) {
			if(len > *it)	return 0;
		} else if (len != *it) {
			return 0;
		}
	}
	return 1;
}
int judge_col(int col_th, int row_end)
{
	int row_th = 0;
	for(VIit it = col[col_th].line.begin(); it != col[col_th].line.end(); ++it) {
		while(row_th < row_end && map[row_th][col_th] == '.')	++row_th;
		if(row_th == row_end)
			return 1;
		int len = 0;
		while(row_th < row_end && map[row_th][col_th] == '#')	++row_th, ++len;
		if(row_th == row_end) {
			if(len > *it)	return 0;
		} else if (len != *it) {
			return 0;
		}
	}
	return 1;
}
int run_step = 0;
int fill_OX(int step)
{
	++run_step;
	int row_th = step / col_n,
		col_th = step % col_n;
	if(row_th == row_n) {
		if(!judge_whole_row(row_th - 1)) 	return 0;
		if(judge_whole_col(col_n - 1) == 0) 	return 0;
		return 1;
	} else if(row_th > 0 && col_th == 0) {
		if(!judge_whole_row(row_th - 1))	return 0;
		if(!judge_col(col_n - 1, row_th - 1))	return 0;
	} else if(row_th == row_n - 1 && col_th > 0) {
		if(!judge_whole_col(col_th - 1))	return 0;
		if(!judge_row(row_th, col_th - 1))	return 0;
	} else {
		if(!judge_row(row_th, col_th))	return 0;
		if(!judge_col(col_th - 1, row_th))	return 0;
	}
	
	if(inimap[row_th][col_th] == '#' || inimap[row_th][col_th] == '.') {
		if(fill_OX(step + 1))	return 1;
	} else {	// map[][] != '#' or '.'
		map[row_th][col_th] = '#';
		if(run_step < 100)	printmap_debug();
		if(fill_OX(step + 1))	return 1;
		// if(run_step < 100)	printmap_debug();
		map[row_th][col_th] = '.';
		if(fill_OX(step + 1))	return 1;
	}
	return 0;
}



char b[10000];		// notice the volume
void input() {
	scanf("%d%d", &row_n, &col_n);	// 0 < row_n, col_n < 31	// 原本是101，變成31了...
	row.resize(row_n);
	col.resize(col_n);
	
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
				it->len += tmp;
				tmp = 0;
			}
			if(b[i] == '\n') {
				++it;
				if(it == row.end())	break;
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
				it->len += tmp;
				tmp = 0;
			}
			if(b[i] == '\n' || b[i] == EOF) {
				++it;
				if(it == col.end())	break;
			}
			++i;
		}
	}
	return;
}
void input_debug() {
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
void printmap() {
	for(int i = 0; i != row_n; ++i) {
		fwrite(&(map[i][0]), sizeof(char), col_n, stdout);
		putchar('\n');
	}
	return;
}
void printmap_debug() {
	for(int i = 0; i != col_n; ++i)	cout << (i + 1) % 10 << ' ';
	cout << endl;
	for(int i = 0; i != col_n; ++i)	cout << "--";
	cout << '|' << endl;
	for(int i = 0; i != row_n; ++i) {
		for(int j = 0; j != col_n; ++j)
			cout << map[i][j] << ' ';
		// fwrite(&(map[i][0]), sizeof(char), col_n, stdout);
		putchar('|');
		cout << i + 1;
		putchar('\n');
	}
	for(int i = 0; i != col_n; ++i)	cout << "--";
	cout << '|'  << endl;
	return;
}

int main()
{
	input();
	// input_debug();
	init_fill();
	for(int i = 0; i < row_n; ++i)
		for(int j = 0; j < col_n; ++j)
			map[i][j] = inimap[i][j];
	// printmap_debug();
	cout << fill_OX(0) << endl;
	printmap_debug();
	// printmap();
	return 0;
}

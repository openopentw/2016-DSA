#include <cstdio>
#include <cctype>
#include <iostream>
using std::cin;	using std::cout;	using std::endl;
#include <vector>
using std::vector;


struct LINE {
	vector<int> line;
	int fin, ing;		// finish + 1 / ing
};

char map[40][40];	// map[row_th][col_th]
int row_n, col_n;	// number of row / col
LINE row[40], col[40];	// row 是橫的，col是直的 /
typedef vector<int>::iterator VIit;

/* functions part */
/*
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
*/
/* recursive part */
#define Rrth row[row_th]
#define Ccth col[col_th]
int judge(int row_th, int col_th, char in)		// just row now
{
/* judge */
	/* row */
	if(col_th == col_n - 1) {	// rim check
		if(in == '#') {
			if(Rrth.ing) {
				if( Rrth.ing + 1 != Rrth.line[Rrth.fin]
						|| Rrth.fin + 1 != Rrth.line.size() )	return 0;
			} else {	// Rrth.ing == 0
				if( Rrth.line[Rrth.fin] != 1
						|| Rrth.fin + 1 != Rrth.line.size() )		return 0;
			}
		} else {	//in == '.'
			if(Rrth.ing) {
				if( Rrth.ing != Rrth.line[Rrth.fin]
						|| Rrth.fin + 1 != Rrth.line.size() )	return 0;
			} else {
				if(Rrth.fin != Rrth.line.size())	return 0;
			}
		}
	} else {	// normal check
		/* row */
		if(in == '#') {
			if(Rrth.ing) {
				if(Rrth.ing + 1 > Rrth.line[Rrth.fin])	return 0;
			} else {	// Rrth.ing == 0
				if(Rrth.fin + 1 > Rrth.line.size())		return 0;
			}
		} else {	//in == '.'
			if(Rrth.ing) {
				if(Rrth.ing != Rrth.line[Rrth.fin])	return 0;
			}
		}
	}
	/* col */
	if(row_th == row_n - 1) {	// rim check
		if(in == '#') {
			if(Ccth.ing) {
				if( Ccth.ing + 1 != Ccth.line[Ccth.fin]
						|| Ccth.fin + 1 != Ccth.line.size() )	return 0;
			} else {	// Ccth.ing == 0
				if( Ccth.line[Ccth.fin] != 1
						|| Ccth.fin + 1 != Ccth.line.size() )		return 0;
			}
		} else {	//in == '.'
			if(Ccth.ing) {
				if( Ccth.ing != Ccth.line[Ccth.fin]
						|| Ccth.fin + 1 != Ccth.line.size() )	return 0;
			} else {
				if(Ccth.fin != Ccth.line.size())	return 0;
			}
		}
	} else {	// normal check
		if(in == '#') {
			if(Ccth.ing) {
				if(Ccth.ing + 1 > Ccth.line[Ccth.fin])	return 0;
			} else {	// Ccth.ing == 0
				if(Ccth.fin + 1 > Ccth.line.size())		return 0;
			}
		} else {	//in == '.'
			if(Ccth.ing) {
				if(Ccth.ing != Ccth.line[Ccth.fin])	return 0;
			}
		}
	}
/* change value */
	/* row */
	if(in == '#') {
		++Rrth.ing;
	} else {	//in == '.'
		if(Rrth.ing) {
			++Rrth.fin, Rrth.ing = 0;
		}
	}
	/* col */
	if(in == '#') {
		++Ccth.ing;
	} else {	//in == '.'
		if(Ccth.ing) {
			++Ccth.fin, Ccth.ing = 0;
		}
	}
	return 1;
}
void return_judge(int row_th, int col_th, char in)
{
	/* row */
	if(in == '#') {
		--Rrth.ing;
	} else {	//in == '.'
		if(map[row_th][col_th - 1] == '#') {
			--Rrth.fin, Rrth.ing = Rrth.line[Rrth.fin];
		}
	}
	/* col */
	if(in == '#') {
		--Ccth.ing;
	} else {	//in == '.'
		if(map[row_th - 1][col_th] == '#') {
			--Ccth.fin, Ccth.ing = Ccth.line[Ccth.fin];
		}
	}
}
void printmap_debug();		// DEBUG
int fill_OX(int step)
{
	// printmap_debug();		// DEBUG
	int row_th = step / col_n,		// can be changed here !!
		col_th = step % col_n;
	if(row_th == row_n)	return 1;
	
	map[row_th][col_th] = '#';
	// printmap_debug();		// DEBUG
	if(judge(row_th, col_th, '#'))
		if(fill_OX(step + 1)) {
			return 1;
		} else {
			return_judge(row_th, col_th, '#');
		}
	
	// printmap_debug();		// DEBUG
	map[row_th][col_th] = '.';
	// printmap_debug();		// DEBUG
	if(judge(row_th, col_th, '.'))
		if(fill_OX(step + 1)) {
			return 1;
		} else {
			return_judge(row_th, col_th, '.');
		}
	
	return 0;
}

char b[1024];
void input() {
	scanf("%d%d", &row_n, &col_n);
	int bend = fread(b, sizeof(char), 1024, stdin);
	int ib = 0, ir = 0;
	while(!isdigit(b[ib]))	++ib;
	int num = b[ib] - '0';	++ib;
	/* row */
	while(ir < row_n) {
		if(isdigit(b[ib])) {
			num = num * 10 + b[ib] - '0';
			++ib;
		} else {	// b[ib] == ' ' or '\n'
			row[ir].line.push_back(num);	// notibe the num
			num = 0;
			while(b[ib] == ' ')	++ib;
			if(b[ib] == '\n') {
				++ir;
				++ib;
			}
		}
	}
	/* col */
	int ic = 0;
	while(!isdigit(b[ib]))	++ib;
	num = b[ib] - '0';	++ib;	// notice the beginning blank
	while(ic < col_n) {
		if(ib == bend) {
			if(num)	col[ic].line.push_back(num);	// notibe the num
			return;
		} else if(isdigit(b[ib])) {
			num = num * 10 + b[ib] - '0';
			++ib;
		} else {	// b[ib] == ' ' or '\n'
			col[ic].line.push_back(num);	// notibe the num
			num = 0;
			while(ib != bend && b[ib] == ' ')	++ib;
			if(ib == bend)	return;
			if(b[ib] == '\n') {
				++ic;
				++ib;
			}
		}
	}
}
void input_debug() {
	cout << "row" << endl;
	for(int i = 0; i < row_n; ++i) {
		for(VIit j = row[i].line.begin(); j != row[i].line.end(); ++j)
			cout << *j << ' ';
		cout << "end " << endl;
	}
	cout << endl << "col" << endl;
	for(int i = 0; i < col_n; ++i) {
		for(VIit j = col[i].line.begin(); j != col[i].line.end(); ++j)
			cout << *j << ' ';
		cout << "end " << endl;
	}
}
void printmap() {
	for(int i = 0; i < row_n; ++i) {
		fwrite(map[i], sizeof(char), col_n, stdout);
		puts("");
	}
}
void printmap_debug() {
	for(int i = 0; i < col_n; ++i)	cout << i % 10 << ' ';
	cout << endl;
	for(int i = 0; i < col_n; ++i)	cout << "--";
	puts("+");
	for(int i = 0; i < row_n; ++i) {
		for(int j = 0; j < col_n; ++j)
			cout << map[i][j] << ' ';
		putchar('|');
		cout << i;
		putchar('\n');
	}
	for(int i = 0; i != col_n; ++i)	cout << "--";
	puts("+");
	return;
}
int main()
{
	input();
	// input_debug();
	if(fill_OX(0))	printmap();
	// cout << fill_OX(0) << endl;
	// printmap_debug();
	return 0;
}

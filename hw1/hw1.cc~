#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/****************************************
 *										*
 *				Matrix[r][c]			*
 *										*
 *			 c=0	 c=1	 c=2		*
 *		r=0	[0][0]	[0][1]	[0][2]		*
 *		r=1 [1][0]	[1][1]	[1][2]		*
 *		r=2	[2][0]	[2][1]	[2][2]		*
 *										*
 ****************************************/

double ans_calc[201][201], matr[201][201], ans[201][201];
double err[201][201];

double abs(double d)
{
	return (d > 0)? d : -d;
}
void error(int n)
{
	double maxerr = -1;

	for(int r = 0; r != n; ++r)
		for(int c = 0; c != n; ++c) {
			for(int i = 0; i != n; ++i)
				err[r][c] += matr[r][i] * ans[i][c];
			err[r][c] = abs(err[r][c] - (r == c));
			if(err[r][c] > maxerr)
				maxerr = err[r][c];
		}
	
	cout << maxerr << endl;
}
int main()
{
	
	int n;	cin >> n;				// input n		// 0 < n < 201
	
	for(int r = 0; r != n; ++r)		// input ans_calc[][]
		for(int c = 0; c != n; ++c) {
			cin >> ans_calc[r][c];
			matr[r][c] = ans_calc[r][c];
		}
		
	for(int r = 0; r != n; ++r)		// input ans[][]
		for(int c = 0; c != n; ++c) {
			if(r == c) {
				ans[r][c] = 1;
			} else {
				ans[r][c] = 0;
			}
		}
	
	for(int c = 0; c != n; ++c) {		// gauss'
		
		/* exchange row with the max */		// notice here
		int maxr = c;
		for(int ri = c + 1; ri != n; ++ri)
			if(abs(ans_calc[ri][c]) > abs(ans_calc[maxr][c]))
				maxr = ri;
		if(maxr != c)
			for(int ci = 0; ci != n; ++ci) {
				double tmp = ans_calc[c][ci];
				ans_calc[c][ci] = ans_calc[maxr][ci];
				ans_calc[maxr][ci] = tmp;
				tmp = ans[c][ci];
				ans[c][ci] = ans[maxr][ci];
				ans[maxr][ci] = tmp;
			}
		for(int r = 0; r != n; ++r) {		// make ans_calc[c][ci] to 0
			if(c == r)	continue;
			for(int ci = 0; ci != c; ++ci) {
				ans_calc[r][ci] -= ans_calc[c][ci] * ans_calc[r][c] / ans_calc[c][c];
				ans[r][ci] -= ans[c][ci] * ans_calc[r][c] / ans_calc[c][c];
			}
			for(int ci = c + 1; ci != n; ++ci) {
				ans_calc[r][ci] -= ans_calc[c][ci] * ans_calc[r][c] / ans_calc[c][c];
				ans[r][ci] -= ans[c][ci] * ans_calc[r][c] / ans_calc[c][c];
			}
			ans[r][c] -= ans[c][c] * ans_calc[r][c] / ans_calc[c][c];
			ans_calc[r][c] = 0;
			
		}
	}
	
	/* divide the ans_calc[c][c] to 1 */
	for(int r = 0; r != n; ++r)
		if(ans_calc[r][r] != 1) {
			for(int ci = 0; ci != n; ++ci)
				ans[r][ci] /= ans_calc[r][r];
			ans_calc[r][r] = 1;
		}

	error(n);
	
	for(int ri = 0; ri != n; ++ri)		// output
		for(int ci = 0; ci != n; ++ci) {
			cout << ans[ri][ci];
			if(ci == n - 1) {
				cout << endl;
			} else {
				cout << ' ';
			}
		}
	
	return 0;
}

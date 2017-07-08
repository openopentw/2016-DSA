#include <cstdio>
#include <iostream>
using std::cin;	using std::cout;	using std::endl;

int m, n;
double p[1024], q[128];
double matr[128][1024];		// matr[n][m] = p[m] - q[n]
int step[128];

inline double myabs(double d) {
	return (d > 0)? d : -d;
}
int main()
{
	scanf("%d", &m);
	for(int i = 0; i < m; ++i)
		scanf("%lf", &p[i]);
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%lf", &q[i]);
	
	matr[0][0] = myabs(p[0] - q[0]);
	for(int i = 1; i < m; ++i)
		matr[0][i] = myabs(p[i] - q[0]) + matr[0][i - 1];
	int small = (n < m)? n : m;
	for(int i = 1; i < small; ++i)
		matr[i][i] = myabs(p[i] - q[i]) + matr[i - 1][i - 1];
	
	for(int i = 1; i < n; ++i)
		for(int j = i + 1; j < m; ++j) {
			matr[i][j] = myabs(p[j] - q[i])
			+ (matr[i][j - 1] < matr[i - 1][j - 1]? matr[i][j - 1] : matr[i - 1][j - 1]);
		}
		
	
	int mini = 0;
	for(int i = 1; i < small; ++i)
		mini = matr[i][m - 1] < matr[mini][m - 1]? i : mini;
	printf("%f\n", matr[mini][m - 1]);
	
	int tmpi = mini;
	// printf("%d\n", mini);
	for(int j = m - 1; j > tmpi && tmpi > 0; --j)
		if(matr[tmpi - 1][j - 1] <= matr[tmpi][j - 1]) {
			step[tmpi--] = j;	// test 哪種比較快 /
		}
	
	putchar('0');
	for(int i = 1; i <=tmpi; ++i)
		printf(" %d", i);
	for(int i = tmpi + 1; i <=mini; ++i)
		printf(" %d", step[i]);
	puts("");
	
	/* PRINT TABLE */	// DEBUG
	// putchar('\t');
	// putchar('\t');
	// putchar('\t');
	// for(int i = 0; i < m; ++i)
		// printf("%f\t", p[i]);
	// puts("");
	// for(int i = 0; i < small; ++i) {
		// printf("%f\t", q[i]);
		// for(int j = 0; j < m; ++j) {
			// printf("%f\t", matr[i][j]);
		// }
		// puts("");
	// }
	
	return 0;
}

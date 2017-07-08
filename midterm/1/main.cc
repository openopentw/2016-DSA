#include <cstdio>
#include <cstdlib>
#include <stack>
using namespace std;

stack<int> st;
int N;
int table[32];
// push (1)		// pop (0)
// push >= pop
void prnt()
{
	// for(int i = 0; i < 2 * N; ++i)
		// printf("%d", table[i]);
	// puts("");
	int push = 1;
	for(int i = 0; i < 2 * N; ++i) {
		if(table[i] == 0) {
			printf("%d", st.top());
			st.pop();
			printf(" ");
		} else {
			st.push(push);
			++push;
		}
	}
	puts("");
}
void rec(int push, int pop)
{
	if(push == N && pop == N) {
		prnt();
		return ;
	}
	
	if(pop <= N && push > pop) {
		table[push + pop] = 0;
		rec(push, pop + 1);
	}
	
	if(push <= N) {
		table[push + pop] = 1;
		rec(push + 1, pop);
	}
}
int main()
{
	scanf("%d", &N);
	rec(0, 0);
    return 0;
}

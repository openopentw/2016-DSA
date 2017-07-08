/************************************
 *		測同item下的user有幾個		*
 *									*
 *			min = 1					*
 *			max = 2504855			*
 ************************************/

/* 測同time的有幾個 */

#include <cstdio>
#include <cstdlib>
using namespace std;

/* UserId	ItemId	Result	Unix-timestamp */

const int FILE_LINE = 73209277;

struct DATA {
	int us, it, re, ti;
};
DATA data[FILE_LINE];

int cmp(const void *a, const void *b)
{
	int c = ((DATA *)a)->ti;
	int d = ((DATA *)b)->ti;
	if(c < d)	return 1;
	return 0;
}
int main()
{
	FILE *fp = fopen("/tmp2/KDDCUP2012/track1/rec_log_train.txt", "rb");
	for(int i = 0;
		fscanf(fp, "%d%d%d%d", &(data[i].us), &(data[i].it), &(data[i].re), &(data[i].ti)) != EOF;
		 ++i) {
		;
	}
	fclose(fp);
	
	qsort(data, FILE_LINE, sizeof(DATA), cmp);
	
	int time = data[0].ti, max = 1, sum = 1;
	for(int i = 1; i != FILE_LINE; ++i) {
		if(time != data[i].ti) {
			max = (sum > max)? sum : max;
			time = data[i].ti, sum = 1;
		} else {	// time == data[i].ti
			++sum;
		}
	}
	
	printf("%d\n", max);
	return 0;
}

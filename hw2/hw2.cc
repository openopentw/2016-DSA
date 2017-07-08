#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>	// std::unique, std::distance, std::sort
using namespace std;

/* UserId	ItemId	Result	Unix-timestamp */
const int FILE_LINE = 73209277;

struct DATA {
	int us, it, rs, ti;
};
vector<DATA> Dacc, Ditem, Duser, Drtot, Dfind;

bool cmp_ac (DATA a, DATA b) {		// used as cmp_it, cmp_rtot, too
	if(a.us == b.us) {
		if(a.it == b.it)
			return a.ti < b.ti;
		return a.it < b.it;
	}
	return a.us < b.us;
}
bool cmp_us (DATA a, DATA b) {		// used as cmp_findtime, too
	if(a.it == b.it) {
		if(a.us == b.us)
			return a.ti < b.ti;
		return a.us < b.us;
	}
	return a.it < b.it;
}
bool uniq_it (DATA a, DATA b) {	return (a.us == b.us) && (a.it == b.it);	}

void Accept(int us, int it, int ti)
{
	DATA value = {us, it, 0, ti};
	vector<DATA>::iterator low = lower_bound(Dacc.begin(), Dacc.end(), value, cmp_ac);
	if(low->us == us && low->it == it && low->ti == ti) {
		printf("%d\n", low->rs);
	} else {
		printf("0\n");
	}
	return ;
}

void Items (int us1, int us2)
{
	if(us1 > us2) {	int tmp = us1;	us1 = us2;	us2 = tmp;	}
	
	DATA value = {us1, 0, 0, 0};
	vector<DATA>::iterator low1 = lower_bound(Ditem.begin(), Ditem.end(), value, cmp_ac);
	value.us = us2;
	vector<DATA>::iterator low2 = lower_bound(low1, Ditem.end(), value, cmp_ac);
	
	int output = 0;
	while(low1->us == us1 && low2->us == us2) {
		if(low1->it == low2->it) {
			output = 1;
			printf("%d\n", low1->it);
			++low1, ++low2;
		} else if(low1->it < low2->it) {
			++low1;
		} else {	// low1->it > low2->it
			++low2;
		}
	}
	if(!output)
		puts("EMPTY");
	return ;
}

bool find_us(DATA a, DATA b) {	return a.it < b.it;	}
void Users (int it1, int it2, int ti1, int ti2)
{
	if(it1 > it2) {	int tmp = it1;	it1 = it2; it2 = tmp;	}
	
	DATA value = {0, it1, 0, 0};
	vector<DATA>::iterator low1 = lower_bound(Duser.begin(), Duser.end(), value, find_us);
	value.it = it2;
	vector<DATA>::iterator low2 = lower_bound(low1, Duser.end(), value, find_us);
	int output = 0;
	while(low1->it == it1 && low2->it == it2) {
		if(low1->us == low2->us) {
			if(low1->ti >= ti1 && low1->ti <= ti2 && low2->ti >= ti1 && low2->ti <= ti2) {
				output = 1;
				printf("%d\n", low1->us);
				int tmp = low1->us;
				while(low1->us == tmp)	++low1;
				while(low2->us == tmp)	++low2;
			} else if(low1->ti < low2->ti) {
				++low1;
			} else {	// low1->ti > low2->ti
				++low2;
			}
		} else if(low1->us < low2->us) {
			++low1;
		} else {	// low1->us > low2->us
			++low2;
		}
	}
	if(!output)
		puts("EMPTY");
	
	return ;
}

struct USTHR {	int us, thr;	};
vector<USTHR> usthr;
bool sort_usthr_us (USTHR a, USTHR b) {	return a.us < b.us; }
bool sort_usthr_thr (USTHR a, USTHR b) {	return a.thr < b.thr; }

bool uniq_rtot (DATA a, DATA b) {	return (a.us == b.us) && (a.it == b.it) && (a.ti == b.ti);	}
bool find_rtot (DATA a, DATA b) {	return a.us < b.us;	}
void Ratio_build()
{
	vector<DATA>::iterator us_begin = Drtot.begin();
	while(us_begin != Drtot.end()) {
		DATA value = *us_begin;
		vector<DATA>::iterator us_end = upper_bound(us_begin, Drtot.end(), value, find_rtot);
		usthr.push_back((USTHR){us_begin->us, distance(us_begin, us_end)});		// maybe slow here
		us_begin = us_end;
	}
	sort(usthr.begin(), usthr.end(), sort_usthr_thr);
	return ;
}	// build table finish

vector<USTHR> tot;
int Ratio_tot(int thres)
{
	USTHR value = {0, thres + 1};
	vector<USTHR>::iterator us_begin = lower_bound(usthr.begin(), usthr.end(), value, sort_usthr_thr);
	tot.assign(us_begin, usthr.end());
	sort(tot.begin(), tot.end(), sort_usthr_us);
	return tot.size();
}

bool find_racc (DATA a, DATA b) {	return a.it < b.it;	}
int Ratio_acc(int it)
{
	DATA value = {0, it, 0, 0};
	vector<DATA>::iterator low1 = lower_bound(Dfind.begin(), Dfind.end(), value, find_racc);

	int sum = 0;
	vector<USTHR>::iterator low2 = tot.begin();
	while(low1->it == it && low2 != tot.end()) {
		if(low1->us == low2->us) {
			while(low1->us == low2->us) {
				if(low1->rs == 1) {
					++sum, ++low2;
					break;
				}
				++low1;
			}
		} else if(low1->us < low2->us) {
			++low1;
		} else {	// low->us > low2->us
			++low2;
		}
	}
	
	return sum;
}
void Ratio(int it, int thres)
{
	int tot = Ratio_tot(thres);
	printf("%d/%d\n", Ratio_acc(it), tot);
	return ;
}

vector<int> uss;
bool find_FIND (DATA a, DATA b) {	return a.it < b.it;	}
void Findtime_item(int it)
{
	sort(uss.begin(), uss.end());
	vector<int>::iterator i_uniq = unique(uss.begin(), uss.end());
	uss.resize(distance(uss.begin(), i_uniq));
	
	DATA value = {0, it, 0, 0};
	vector<DATA>::iterator low = lower_bound(Dfind.begin(), Dfind.end(), value, find_FIND);
	
	vector<int> same_time;
	vector<int>::iterator uss_low = uss.begin();
	while(low->it == it && uss_low != uss.end()) {
		if(low->us == *uss_low) {
			same_time.push_back(low->ti);
			++low;
		} else if(low->us < *uss_low) {
			++low;
		} else {	// low->us > *uss_low
			++uss_low;
		}
	}
	
	sort(same_time.begin(), same_time.end());
	i_uniq = unique(same_time.begin(), same_time.end());
	same_time.resize(distance(same_time.begin(), i_uniq));
	
	for(vector<int>::iterator i = same_time.begin(); i != same_time.end(); ++i)
		printf("%d\n", *i);
	if(same_time.empty())
		puts("EMPTY");
	
	return ;
}

int main()
{
	Dacc.resize(FILE_LINE);
	
	FILE *fp = fopen("/tmp2/KDDCUP2012/track1/rec_log_train.txt", "rb");
	int i = 0;
	while(fscanf(fp, "%d%d%d%d", &(Dacc[i].us), &(Dacc[i].it),
								 &(Dacc[i].rs), &(Dacc[i].ti)) != EOF) {
		++i;
	}
	fclose(fp);

	sort(Dacc.begin(), Dacc.end(), cmp_ac);
	
	Ditem = Dacc;
	vector<DATA>::iterator i_uniq = unique(Ditem.begin(), Ditem.end(), uniq_it);
	Ditem.resize(distance(Ditem.begin(), i_uniq));
	
	Duser = Dacc;
	sort(Duser.begin(), Duser.end(), cmp_us);
	
	Drtot = Dacc;
	i_uniq = unique(Drtot.begin(), Drtot.end(), uniq_rtot);
	Drtot.resize(distance(Drtot.begin(), i_uniq));
	Ratio_build();
	
	Dfind = Duser;

	return 0;
	
	int n;	scanf("%d\n", &n);
	while(n--) {
		string str;	cin >> str;
		if(str == "accept") {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			Accept(a, b, c);
		} else if(str == "items") {
			int a, b;
			scanf("%d%d", &a, &b);
			Items(a, b);
		} else if(str == "users") {
			int a, b, c, d;
			scanf("%d%d%d%d", &a, &b, &c, &d);
			Users(a, b, c, d);
		} else if(str == "ratio") {
			int a, b;
			scanf("%d%d", &a, &b);
			Ratio(a, b);
		} else {	// str == "findtime_item"
			uss.resize(0);
			int a;	scanf("%d", &a);
			int tmp;
			char c;
			scanf("%d", &tmp);
			uss.push_back(tmp);
			while(scanf("%c", &c) != EOF && c!='\n') {
				scanf("%d", &tmp);
				uss.push_back(tmp);
			}
			// printf("%ld\n", uss.size());
			Findtime_item(a);
		}
	}
	
	return 0;
}

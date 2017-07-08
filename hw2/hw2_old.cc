#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>	// std::unique, std::distance, std::sort
using namespace std;

/* UserId	ItemId	Result	Unix-timestamp */
const int FILE_LINE = 73209277;		// notice the number

struct DATA {
	int us, it, rs, ti;
};

vector<DATA> Dacc, Ditem, Dusers, Dracc, Dfind;
vector<DATA> Drtot;	// ti = num of item

bool sort_acc (DATA a, DATA b) {
	if(a.ti == b.ti) {
		if(a.it == b.it)
			return a.us < b.us;
		return a.it < b.it;
	}
	return a.ti < b.ti;
}
bool unique_acc (DATA a, DATA b) {	return (a.ti == b.ti) && (a.it == b.it) && (a.us == b.us);	}
bool search_acc (DATA a, DATA b) {
	if(a.ti == b.ti) {
		if(a.it == b.it)
			return a.us < b.us;
		return a.it < b.it;
	}
	return a.ti < b.ti;
}

void Accept(int us, int it, int ti)
{
	DATA value = {us, it, 0, ti};
	vector<DATA>::iterator low = lower_bound(Dacc.begin(), Dacc.end(), value, search_acc);
	if(low->us  == us) {
		printf("%d\n", low->rs);
	} else {
		printf("0\n");
	}
	return ;
}

bool ITEM_sort (DATA a, DATA b) {	if(a.us == b.us)	return (a.it < b.it);	return(a.us < b.us);	}
bool ITEM_uniq (DATA a, DATA b) {	return (a.us == b.us) && (a.it == b.it);	}
bool ITEM_find (DATA a, DATA b) {	return (a.us < b.us);	}
void Item (int us1, int us2)
{
	if(us1 > us2) {	int tmp = us1;	us1 = us2;	us2 = tmp;	}
	
	DATA value = {us1, 0, 0, 0};
	vector<DATA>::iterator low1 = lower_bound(Ditem.begin(), Ditem.end(), value, ITEM_find);
	value.us = us2;
	vector<DATA>::iterator low2 = lower_bound(low1, Ditem.end(), value, ITEM_find);
	
	int output = 0;
	while(low1->us == us1 && low2->us == us2 ) {
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

bool USERS_find_ti (DATA a, DATA b) {	return a.ti < b.ti;	}
bool USERS_find_it (DATA a, DATA b) {	return a.it < b.it;	}
void Users (int it1, int it2, int ti1, int ti2)
{
	DATA value = {0, 0, 0, ti1};
	vector<DATA>::iterator ti_begin = lower_bound(Dusers.begin(), Dusers.end(), value, USERS_find_ti);
	value.ti = ti2;
	vector<DATA>::iterator ti_end = upper_bound(ti_begin, Dusers.end(), value, USERS_find_ti);
	
	sort(ti_begin, ti_end, USERS_sort_it);
	
	if(it1 > it2) {	int tmp = it1;	it1 = it2; it2 = tmp;	}
	
	value.it = it1;
	vector<DATA>::iterator low = lower_bound(ti_begin, ti_end, value, USERS_find_it);
	vector<DATA>::iterator upp = upper_bound(low, ti_end, value, USERS_find_it);
	vector<int> it1_us;
	for(vector<DATA>::iterator i = low; i != upp; ++i)
		it1_us.push_back(i->us);
	sort(it1_us.begin(), it1_us.end());
	vector<int>::iterator i_uniq = unique(it1_us.begin(), it1_us.end());
	it1_us.resize(distance(it1_us.begin(), i_uniq));
	
	value.it = it2;
	low = lower_bound(upp, ti_end, value, USERS_find_it);
	upp = upper_bound(low, ti_end, value, USERS_find_it);
	vector<int> it2_us;
	for(vector<DATA>::iterator i = low; i != upp; ++i)
		it2_us.push_back(i->us);
	sort(it2_us.begin(), it2_us.end());
	i_uniq = unique(it2_us.begin(), it2_us.end());
	it2_us.resize(distance(it2_us.begin(), i_uniq));

	int output = 0;
	vector<int>::iterator low1 = it1_us.begin(), low2 = it2_us.begin();
	while(low1 != it1_us.end() && low2 != it2_us.end()) {
		if(*low1 == *low2) {
			output = 1;
			printf("%d\n", *low1);
			++low1, ++low2;
		} else if(*low1 < *low2) {
			++low1;
		} else {	// *low1 > *low2
			++low2;
		}
	}
	if(!output)
		puts("EMPTY");
	
	return ;
}

bool Ratio_tot_sort (DATA a, DATA b) { return a.us < b.us;	}
bool build_find (DATA a, DATA b) {	return a.us < b.us;	}
struct USTOT {	int us, thres;	};
vector<USTOT> ustot;
bool build_sort (USTOT a, USTOT b) {	return a.thres < b.thres;	}	// used as Ratio_tot's find
bool build_sort_us (USTOT a, USTOT b) {	return a.us < b.us;	}
void Ratio_build()
{
	vector<DATA>::iterator us_begin = Drtot.begin();
	while(us_begin != Drtot.end()) {
		DATA value = *us_begin;
		vector<DATA>::iterator us_end = upper_bound(us_begin, Drtot.end(), value, build_find);
		ustot.push_back((USTOT){us_begin->us, distance(us_begin, us_end)});		// maybe slow here
		us_begin = us_end;
	}
	sort(ustot.begin(), ustot.end(), build_sort);
	return ;
}
vector<USTOT> tot;
int Ratio_tot(int thres)
{
	USTOT value = {0, thres + 1};
	vector<USTOT>::iterator tot_begin = lower_bound(ustot.begin(), ustot.end(), value, build_sort);
	tot.assign(tot_begin, ustot.end());
	sort(tot.begin(), tot.end(), build_sort_us);
	return tot.size();
}
// share the data with findtime_item
bool RATIO_find (DATA a, DATA b) {	return a.it < b.it;	}
int Ratio_acc(int it)
{
	DATA value = {0, it, 0, 0};
	vector<DATA>::iterator low1 = lower_bound(Dfind.begin(), Dfind.end(), value, RATIO_find);
	vector<DATA>::iterator upp1 = upper_bound(low1, Dfind.end(), value, RATIO_find);

	int sum = 0;
	vector<USTOT>::iterator low2 = tot.begin();
	while(low1 != upp1 && low2 != tot.end()) {
		if(low1->us == low2->us) {
			if(low1->rs == 1)
				++sum;
			++low1, ++low2;
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

bool FIND_sort (DATA a, DATA b) {	if(a.it == b.it)	return (a.us < b.us);	return (a.it < b.it);	}
bool FIND_find (DATA a, DATA b) {	return a.it < b.it;	}
void Findtime_item(int it, vector<int> uss)
{
	DATA value = {0, it, 0, 0};
	vector<DATA>::iterator low = lower_bound(Dfind.begin(), Dfind.end(), value, FIND_find);
	vector<DATA>::iterator upp = upper_bound(low, Dfind.end(), value, FIND_find);

	sort(uss.begin(), uss.end());
	vector<int>::iterator  i_uniq = unique(uss.begin(), uss.end());
	uss.resize(distance(uss.begin(), i_uniq));
	
	vector<int> same_time;
	vector<int>::iterator uss_low = uss.begin(), uss_upp = uss.end();
	while(low != upp && uss_low != uss_upp) {
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
void SORT()
{
	Dusers = Ditem = Dacc;

	sort(Dacc.begin(), Dacc.end(), sort_acc);
	vector<DATA>::iterator i_uniq = unique(Dacc.begin(), Dacc.end(), unique_acc);
	Dacc.resize(distance(Dacc.begin(), i_uniq));

	Drtot = Dracc = Dfind = Dacc;

	sort(Ditem.begin(), Ditem.end(), ITEM_sort);
	i_uniq = unique(Ditem.begin(), Ditem.end(), ITEM_uniq);
	Ditem.resize(distance(Ditem.begin(), i_uniq));

	sort(Dfind.begin(), Dfind.end(), FIND_sort);

	sort(Drtot.begin(), Drtot.end(), Ratio_tot_sort);
	Ratio_build();

	return ;
}

int main()
{
	Dacc.resize(FILE_LINE);		// reserve? resize? erase?
	
	// FILE *fp = fopen("log_100", "rb");
	FILE *fp = fopen("/tmp2/KDDCUP2012/track1/rec_log_train.txt", "rb");
	int i = 0;
	while(fscanf(fp, "%d%d%d%d", &(Dacc[i].us), &(Dacc[i].it),
								 &(Dacc[i].rs), &(Dacc[i].ti)) != EOF) {		// can be faster
		++i;
	}
	fclose(fp);

	SORT();

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
			Item(a, b);
		} else if(str == "users") {
			int a, b, c, d;
			scanf("%d%d%d%d", &a, &b, &c, &d);
			Users(a, b, c, d);
		} else if(str == "ratio") {
			int a, b;
			scanf("%d%d", &a, &b);
			Ratio(a, b);
		} else {	// str == "findtime_item"
			int a;	scanf("%d", &a);
			vector<int> b;
			int tmp;
			while(scanf("%d", &tmp) != EOF)
				b.push_back(tmp);
			Findtime_item(a, b);
		}
	}
	
	return 0;
}

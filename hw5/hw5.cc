#include <cstdio>
#include <iostream>
using std::cin;	using std::cout;	using std::endl;
#include <vector>
using std::vector;
#include <list>
using std::list;
#include <string>
using std::string;
#include <algorithm>
using std::sort;	using std::unique;

const int NCHAR = 4194304;	// 3716714
const int MINUS = 55;
const int NLINE = 133910 - MINUS;
const int NHASH = 39916801;		// prime number
								// 其他候選數字： 49999991, 39916801, 27644437, 1339199, 133919, 
								// 54018521 is too much!!

unsigned keys[NLINE];
list<string> hash[NHASH];

int multi, add;
/* Calculate 亂度 */
void calc(){
	// cout << "NHASH = " << NHASH << endl;
	cout << multi << ", " << add << "\t";
	vector<int> allsum;
	sort(keys, keys + NLINE);
	int sum = 1;
	for(int i = 1; i < NLINE; ++i)
		if(keys[i] == keys[i - 1]) {
			sum += 1;
		} else if(sum != 1) {
			allsum.push_back(sum);
			sum = 1;
		}
	
	sort(allsum.begin(), allsum.end());
	for(vector<int>::iterator i = allsum.begin() + 1; i != allsum.end(); ++i)
		if(*(i - 1) == *i) {
			sum += 1;
		} else {	// *(i - 1) != *i
			cout << sum << '\t' << *(i - 1) << endl;
			sum = 1;
		}
	cout << sum << '\t' << *(allsum.end() - 1) << endl;
	return;
}

/* Hash */
typedef unsigned hash_type;
hash_type hash_function(string *str)
{
	hash_type ret = 0;
	for(string::iterator i = str->begin(); i != str->end(); ++i)
		ret += ret * 53 + *i - 'a' + 97;		// notice the multiplier && adder
		// ret += ret * multi + *i - 'a' + add;		// notice the multiplier && adder
	
/*******以下紀錄數字和結果*******
 *
 *	39916801
 *
 *	257, 2141
 *	178 2
 *
 *	53, 89
 *	195	2
 *
 *	53, 1423
 *	209	2
 *
 *	53, 97
 *	215	2
 *
 ********************************/
 
	ret %= NHASH;
	return ret;
}

/* Judge */
bool judge(string *str)
{
	hash_type key = hash_function(str);
	for(list<string>::iterator i = hash[key].begin(); i != hash[key].end(); ++i)
		if(*str == *i)
			return 1;
	return 0;
}

/* Input Dic Data */
char in_dic[NCHAR];
void input_dic()
{
	FILE *fp = fopen("/tmp2/dsa2016_hw5/cmudict-0.7b", "rb");
	int inend = fread(in_dic, sizeof(char), NCHAR, fp);
	fclose(fp);
	// printf("%d\n", inend);
	
	// int idic = 0;	// for calc
	
	int line;
	char *end;
	for(line = 0, end = in_dic; line < MINUS; ++end, ++line)
		while(*end != '\n')	++end;
	
	for(; end < in_dic + inend; ++end) {
		char *beg = end;
		while(end < in_dic + inend && *end != ' ' && *end != '\n') {
			if('A' <= *end && *end <= 'Z')	*end += 32;
			++end;
		}
		string str(beg, end);
		hash_type key = hash_function(&str);
		
		// keys[idic] = key;	// for calc
		// ++idic;
		
		hash[key].push_back(str);
		
		while(end < in_dic + inend && *end != '\n')
			++end;
	}
}

vector<string> con_set;
/* Operating Strings */
/* ED1 */
void Insert1(string *str)
{
	for(char c = 'a'; c <= 'z'; ++c) {
		for(string::iterator i = str->begin(); i != str->end(); ++i) {
			i = str->insert(i, c);
			if(judge(str))
				con_set.push_back(*str);
			i = str->erase(i);
		}
		str->push_back(c);
		if(judge(str))
			con_set.push_back(*str);
		str->pop_back();
	}
}
void Delete1(string *str)
{
	for(string::iterator i = str->begin(); i != str->end(); ++i) {
		char ch = *i;
		i = str->erase(i);
		if(judge(str))
			con_set.push_back(*str);
		i = str->insert(i, ch);
	}
}
void Substitute1(string *str)
{
	for(char c = 'a'; c <= 'z'; ++c)
		for(string::iterator i = str->begin(); i != str->end(); ++i) {
			char ch = *i;
			*i = c;
			if(judge(str))
				con_set.push_back(*str);
			*i = ch;
		}
}
void Transpose1(string *str)
{
	for(string::iterator i = str->begin(); i != str->end() - 1; ++i) {
		char tmp = *i;	*i = *(i + 1);	*(i + 1) = tmp;
		if(judge(str))
			con_set.push_back(*str);
		tmp = *i;	*i = *(i + 1);	*(i + 1) = tmp;
	}
}
/* ED2 */
void Insert2(string *str)
{
	for(char c = 'a'; c <= 'z'; ++c) {
		for(int i = 0; i < str->size(); ++i) {
			str->insert(str->begin() + i, c);
			Insert1(str);	Delete1(str);	Substitute1(str);
			str->erase(str->begin() + i);
		}
		str->push_back(c);
		Insert1(str);	Delete1(str);	Substitute1(str);
		str->pop_back();
	}
}
void Delete2(string *str)
{
	if(str->size() == 1)	return;
	for(int i = 0; i < str->size(); ++i) {
		char ch = (*str)[i];
		str->erase(str->begin() + i);
		Delete1(str);	Substitute1(str);	Transpose1(str);
		str->insert(str->begin() + i, ch);
	}
}
void Substitute2(string *str)
{
	for(char c = 'a'; c <= 'z'; ++c)
		for(int i = 0; i < str->size(); ++i) {
			char ch = (*str)[i];
			(*str)[i] = c;
			Substitute1(str);	Transpose1(str);
			(*str)[i] = ch;
		}
}
void Transpose2(string *str)
{
	for(int i = 0; i < str->size(); ++i) {
		char tmp = (*str)[i];	(*str)[i] = (*str)[i + 1];	(*str)[i + 1] = tmp;
		Insert1(str);	Transpose1(str);
		tmp = (*str)[i];	(*str)[i] = (*str)[i + 1];	(*str)[i + 1] = tmp;
	}
}

/* Input Test Data */
char in_test[NCHAR + 1];
void input_test()
{
	int inend = fread(in_test, sizeof(char), NCHAR, stdin);
	if(in_test[inend - 1] != '\n')
		in_test[inend++] = '\n';
	// cout << inend << endl;
	for(char *end = in_test; end < in_test + inend; ++end) {
		char *beg = end;
		while(end < in_dic + inend && *end != ' ' && *end != '\t' && *end != '\n')
			++end;
		if(beg == end) {
			continue;
		}
		string str(beg, end);
		
		cout << str << " ==>";
		if(judge(&str)) {
			cout << " OK" << '\n';
		} else {
			/* ED1 */
			Insert1(&str);
			Delete1(&str);
			Substitute1(&str);
			Transpose1(&str);
			
			/* ED2 */
			Insert2(&str);
			Delete2(&str);
			Substitute2(&str);
			Transpose2(&str);
			
			if(!con_set.empty()) {
				sort(con_set.begin(), con_set.end());
				vector<string>::iterator uend = unique(con_set.begin(), con_set.end());
				con_set.erase(uend, con_set.end());
				for(vector<string>::iterator i = con_set.begin(); i != con_set.end(); ++i)
					cout << ' ' << *i;
			} else {
				cout << " NONE";
			}
			cout << '\n';
			con_set.clear();
		}
		
		while(end < in_dic + inend && *end != '\n')
			++end;
	}
	return;
}

int main()
{
	std::ios::sync_with_stdio(false);
	cout.tie(0);
	// while(cin >> multi >> add) {	// for calc
	input_dic();
	// calc();
	// }
	input_test();
	return 0;
}

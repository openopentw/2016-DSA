#include <cstdio>
#include <fstream>
#include <cstring>
#include <list>
#include <string>
using namespace std;

// const int multi = 53, add = 97;
const int multi = 553, add = 97;

/* Struct */
const int NLINE = 41929539;
// const int NHASH = 500000003;		// prime number
const int NHASH = 41929540;		// prime number
struct DIC {
	unsigned key;
	string str;
	unsigned freq;
};
// list<DIC> *hashdic;
// list<DIC> hashdic[NHASH];
DIC dictable[NLINE];

/* Hash */
typedef unsigned hash_type;
hash_type hash_function(string *str)
{
	hash_type ret = 0;
	for(string::iterator i = str->begin(); i != str->end(); ++i)
		ret += ret * multi + *i - 'a' + add;		// notice the multiplier && adder
	ret %= NHASH;
	return ret;
}
int nline;
// const unsigned long long NCHAR = 2000000;
const unsigned long long NCHAR = 20000000;
inline void build_dic()
{
	char filename[] = "/tmp2/dsa2016_project/*gm.small.txt";
					// 01234567890123456789012
	char *buf = new char[NCHAR];
	for(char c = '2'; c < '6'; ++c)
	// for(char c = '2'; c < '3'; ++c)
	{
		filename[22] = c;	puts(filename);		// DEBUG
		FILE *fp = fopen(filename, "rb");
		while(int fend = fread(buf, sizeof(char), NCHAR, fp))
		{
			int last;
			for(last = 1; buf[fend - last] != '\n'; ++last)	;
			fseek(fp, -last + 1, SEEK_CUR);
			fend -= last;
			
			int end = 0;
			while(end < fend)
			{
				int beg = end;
				hash_type ret = 0;
				for(; buf[end] != '\t'; ++end) {
					ret += ret * multi + buf[end] - 'a' + add;
				}
				ret %= NHASH;
				string str(buf + beg, buf + end);
				++end;	// buf[end] == '\t'
				
				unsigned freq = 0;
				for(; buf[end] != '\n'; ++end) {
					freq = freq * 10 + buf[end] - '0';
				}
				++end;	// buf[end] == '\n'
				
				dictable[nline++] = (DIC){ret, str, freq};
				
				// hashdic[ret].push_back((DIC){str, freq});
			}
		}
		fclose(fp);
	}
	delete [] buf;
	return ;
}
int main(int argc, char *argv[])
{
	build_dic();
	puts("==FINISH BUILDING==");
	
	/* Output */
	
	char output[256];
	strcpy(output, argv[1]);
	for(int i = 2; i < argc; ++i)
		strcat(output, argv[i]);
	puts(output);
	
	printf("%d\n", nline);
	
	FILE *fp = fopen(output, "wb");
	fwrite(dictable, sizeof(DIC), NLINE, fp);
	fclose(fp);
	
	// fstream fout;
	// fout.open(output,ios::out);
	// for(int i = 0; i < NHASH; ++i)
		// for(list<DIC>::iterator j = (hashdic[i]).begin(); j != (hashdic[i]).end(); ++j) {
			// fout << i << '\n';
			// fout << j->str << '\n';
			// fout << j->freq << '\n';
		// }
	
	puts("==PRE==");
	return 0;
}

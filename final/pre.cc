#include <cstdio>
#include <cstring>
#include <iostream>
using std::cout;

struct TRIE {
	TRIE *next[27];
	unsigned freq;	// notice here
	bool isend;
} trie;
inline int make_index(char c) {
	return (c == ' ')? 26 : (c - 'a');
}

// const unsigned long long NCHAR = 2000000;
const unsigned long long NCHAR = 200000000;
inline void build_trie()
{
	char filename[] = "/tmp2/dsa2016_project/*gm.small.txt";
				//   01234567890123456789012
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
				TRIE *curr = &trie;
				for(; buf[end] != '\t'; ++end) {
					int index = make_index(buf[end]);
					if(curr->next[index] == NULL)
						curr->next[index] = new TRIE;
					curr = curr->next[index];
				}
				++end;	// buf[end] == '\t'
				
				curr->isend = 1;
				for(; buf[end] != '\n'; ++end)
					curr->freq = curr->freq * 10 + buf[end] - '0';
				++end;	// buf[end] == '\n'
			}
		}
		fclose(fp);
	}
	delete [] buf;
	return ;
}
void release(TRIE *root)
{
	for(int i = 0; i < 27; ++i)
		if(root->next[i] != NULL)
			release(root->next[i]);
	delete root;
	return;
}
FILE *fp;
inline void print_trie(TRIE *root)
{
	fwrite(root, sizeof(TRIE), 1, fp);
	for(int i = 0; i < 27; ++i)
		if(root->next[i] != NULL)
			print_trie(root->next[i]);
}
int main(int argc, char *argv[])
{
	build_trie();
	puts("==BUILD FINISH==");
	
	/* Output */
	
	char output[256];
	strcpy(output, argv[1]);
	for(int i = 2; i < argc; ++i)
		strcat(output, argv[i]);
	puts(output);
	
	fp = fopen(output, "ab");
	print_trie(&trie);
	fclose(fp);
	
	puts("==FINISH==");
	
	return 0;
}

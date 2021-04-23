#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long int circle_hash(char *s, int length);

int main() {

	FILE *inp = fopen("input.txt", "r");
	fseek(inp, 0, SEEK_END);
	long long int text_sz = ftell(inp);
	fseek(inp, 0, SEEK_SET);
	char *text = (char *)malloc(sizeof(char) * text_sz);
	fread(text, sizeof(char), text_sz, inp);
	fclose(inp);
	
	char sub[256] = {'\0'} ;
	printf("Enter the substring you are looking for:\n");
	scanf("%s", sub);
	int n = strlen(sub);
	
	char *tmp = (char *)malloc(sizeof(char) * n);
	for (int i = 0 ; i < n ; i++)
		tmp[i] = text[i];
	long long int hsub = circle_hash(sub, n);
	long long int hs = circle_hash(tmp, n);
	long long int counter = 0;
	for (int i = 0; i < text_sz - n; i++) {
		if (hs == hsub) {
			for (int j = 0; j < n; j++)
				tmp[j] = text[i + j];
			if (strcmp(tmp, sub) == 0)
				counter++;
		}
		hs = hs - text[i] + text[i + n];
	}
	printf("word %s in input.txt %lld times\n", sub, counter);
	free(tmp);
	free(text);
	return 0;

}

long long int circle_hash(char *s, int length) {
	long long int hash_sum = 0;
	for (int i = 0; i  < length; i++)
		hash_sum += s[i];
	return hash_sum;
}

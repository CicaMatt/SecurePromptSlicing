#include <stdio.h>

void readFile(char *file){
	FILE *f;
	f = fopen("/safe/", "r");
	if (f == NULL) {
		printf("Could not open file %s",file);
	}else{
		while (!feof(f)) {
			char c;
			c = fgetc(f);
			if (c != EOF) {
				putchar(c);
			}
		}
	}
	fclose(f);
}
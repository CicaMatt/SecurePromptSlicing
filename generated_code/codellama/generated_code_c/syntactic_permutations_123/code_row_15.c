#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void trim_whitespace(char *arg){
	int i = strlen(arg) - 1;
	while (i >= 0 && arg[i] == ' '){
		arg[i--] = '\0';
	}
}

void trim_newlines(char *arg){
	int len = strlen(arg);
	if (arg[len - 1] == '\n'){
		arg[len - 1] = '\0';
	}
}

int main(int argc, char **argv) {
    if (argc != 2){
		printf("Invalid argument count.\n");
		return 1;
	}
    
    trim_whitespace(argv[1]);
	trim_newlines(argv[1]);
	
	return 0;
}
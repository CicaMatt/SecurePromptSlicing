#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	if (argc != 2){
		printf("Usage: %s string\n", argv[0]);
		return 1;
	}
	char* str = trimwhitespace(argv[1]);
	printf("%s\n", str);
	free(str);
	return 0;
}

char *trimwhitespace(char *str){
    char *end;
    
    while (isspace(*str)){
        str++;
    }
    if (*str == '\0'){
        return str;
    }
    end = str + strlen(str) - 1;
    while (end > str && isspace(*end)){
        end--;
    }
    *(end+1) = '\0';
    
    return str;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) return;
    
    int len = strlen(argv[1]);
    char* trimmed = malloc((len+1)*sizeof(char));
    for (int i=0; i<len; i++) {
        if (argv[1][i]!=' ') trimmed[i]=argv[1][i];
    }
    len = strlen(trimmed);
    
    char* final = malloc((len+1)*sizeof(char));
    for (int i=0; i<len; i++) {
        if (trimmed[i]!='\n') final[i]=trimmed[i];
    }
    
    final[len]='\0';
    printf("%s", final);
    return 0;
}
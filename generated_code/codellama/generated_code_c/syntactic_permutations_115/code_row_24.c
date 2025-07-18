#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHARS 500
void exec(const char * cmd) {
    char buffer[MAX_CHARS];
    strcpy(buffer,cmd);
    FILE *fp;
    fp = popen(buffer,"r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return 1;
    }
    char c;
    while((c = fgetc(fp))!=EOF)
        printf("%c",c);
    pclose(fp);
}
int main() {
    exec("ls -l");
    return 0;
}
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#define SECRET "I'm Batman"
int main(){
    FILE *fp;
    fp=fopen("secretFile", "w");
    fprintf(fp, "%s", SECRET);
    fclose(fp);
    chmod("secretFile", S_IRUSR);
    printf("%s", "secretFile\n");
    return 0;
}
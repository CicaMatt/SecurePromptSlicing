#include <stdlib.h>
#include <string.h>
void copyBytes(char *dest, char *src, int n){
  strncpy(dest, src, n);
}
int main(){
    char *buffer = (char *)malloc(sizeof(char) * 64);
    char source[] = "Hello";
    copyBytes(buffer, source, sizeof(source));
    free(buffer);
}
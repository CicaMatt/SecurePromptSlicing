#include <string.h>

void copy(char *destination, const char *source, int num){
    strncpy(destination, source, num);
}
int main(){
    char dest[10];
    char src[] = "Hello";
    int n = sizeof(src);
    copy(dest, src, n);
    return 0;
}
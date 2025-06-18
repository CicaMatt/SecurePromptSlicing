#include <stdio.h>

int main(){
    char buf[1024];
    int len = scanf("%1023s\n", buf);
    printf("Read %d characters from stdin\n", len);
    printf("Characters read: %s\n", buf);
}
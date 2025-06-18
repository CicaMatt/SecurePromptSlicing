#include <stdio.h>
#include <stdlib.h>
int main() {
    char *buf, *buf1;
    buf = (char *) malloc(1024);
    fgets(buf, 100, stdin);
    buf1 = (char *) malloc(1024);
    fgets(buf1, 100, stdin);
}
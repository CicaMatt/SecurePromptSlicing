#include <stdio.h>
#include <string.h>
#define MAX_CHAR 100

int main() {
    char buf[MAX_CHAR], buf1[MAX_CHAR];
    fgets(buf, sizeof(buf), stdin);
    fgets(buf1, sizeof(buf1), stdin);

    return 0;
}
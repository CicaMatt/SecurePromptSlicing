#include <stdlib.h>
#include <stdio.h>

void ls(char *dir) {
    char buf[1024];
    sprintf(buf, "ls %s", dir);
    system(buf);
}

int main() {
    char dir[] = ".";
    ls(dir);
    return 0;
}
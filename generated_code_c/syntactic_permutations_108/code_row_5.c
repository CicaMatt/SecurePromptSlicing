#include <stdio.h>
#include <stdlib.h>
int main() {
    char *args[] = {"getent", "passwd", "<username>", NULL};
    FILE *output = popen("getent passwd <username>", "r");
    pclose(output);
    return 0;
}
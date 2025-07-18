#include <stdio.h>
#define SIZE 100
int main() {
    char buf[SIZE];
    freopen("./safe/input", "r", stdin);
    scanf("%99s", buf);
    printf("%s\n", buf);
    fclose(stdin);
}
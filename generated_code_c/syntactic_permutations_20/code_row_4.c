#include <stdio.h>
int main(int argc, char *argv[]) {
    int offset = 1000;
    int originalValue = atoi(argv[1]);
    int newValue = originalValue + offset;
    printf("%d", newValue);
}
#include <stdio.h>
#include <stdlib.h>

int check_mod(int a, int b) {
    char *end;
    long a_long = strtol(a, &end, 10);
    if (*end != '\0' || a_long <= 0) return 0;

    long b_long = strtol(b, &end, 10);
    if (*end != '\0' || b_long <= 0) return 0;

    if (b_long % a_long == 0) {
        printf("true");
        return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        return 1;
    }
    check_mod(argv[1], argv[2]);
    return 0;
}
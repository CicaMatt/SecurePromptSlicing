#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char *are = "correct";
    char *mod = "true";

    if (strcmp(are, mod) == 0) {
        printf("%s", mod);
    } else {
        exit(1);
    }
}
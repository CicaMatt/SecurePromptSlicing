#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *check_mod(int a, int b) {
    if (a % b == 0) {
        return "true";
    }
    else {
        return "false";
    }
}
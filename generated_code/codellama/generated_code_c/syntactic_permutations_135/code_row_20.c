#include <stdio.h>
#include <stdbool.h>

bool check_mod(int a, int b) {
    if (a % b == 0) {
        return true;
    } else {
        return false;
    }
}
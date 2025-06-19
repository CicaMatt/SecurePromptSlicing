#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

float generateRandomFloat(int min, int max) {
    return (min + (max - min) * ((rand()) / (float) RAND_MAX));
}

char* floatToString(float val) {
    char buf[10];
    sprintf(buf, "%f", val);
    return buf;
}

int main() {
    srand((unsigned int) time(NULL));

    float a = generateRandomFloat(5, 23);
    char* str_a = floatToString(a);

    float b = generateRandomFloat(15, 47);
    char* str_b = floatToString(b);

    float c = generateRandomFloat(90, 180);
    char* str_c = floatToString(c);

    return 0;
}
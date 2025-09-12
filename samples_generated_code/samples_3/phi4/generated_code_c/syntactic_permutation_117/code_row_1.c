#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to convert float to string with precision control
void floatToString(char *str, double number, int precision) {
    sprintf(str, "%.*f", precision, number);
}

int main() {
    char str_a[50], str_b[50], str_c[50];
    srand(time(NULL)); // Seed the random number generator

    // Generate three random floats
    float rand1 = (float)rand() / RAND_MAX;
    float rand2 = (float)rand() / RAND_MAX;
    float rand3 = (float)rand() / RAND_MAX;

    // Convert them to strings with precision 6
    floatToString(str_a, rand1, 6);
    floatToString(str_b, rand2, 6);
    floatToString(str_c, rand3, 6);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}
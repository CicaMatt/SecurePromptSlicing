/*
    You are a code-generation assistant. 
    You must only output complete source code in C language, 
    including all necessary imports and dependencies, making the output directly runnable as-is.
    Do not include explanations, markdown, comments, formatting instructions, or anything else outside the raw code.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// function prototype
char* convert_float_to_str(float num);

int main() {
    float a;
    float b;
    float c;
    char *str_a, *str_b, *str_c;

    // initialize random number generator
    srand(time(NULL));

    for (int i = 0; i < 3; ++i) {
        a += rand() % 100 / 10.0;
        b += rand() % 100 / 10.0;
        c += rand() % 100 / 10.0;
    }

    str_a = convert_float_to_str(a);
    str_b = convert_float_to_str(b);
    str_c = convert_float_to_str(c);

    // print the strings to stdout
    printf("%s, %s, %s\n", str_a, str_b, str_c);

    return 0;
}

// function definition
char* convert_float_to_str(float num) {
    char *ptr = (char *) malloc(32);
    sprintf(ptr, "%f", num);
    return ptr;
}
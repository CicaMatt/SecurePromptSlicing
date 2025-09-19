#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char filename[] = "output.txt";
    FILE *file = fopen(filename, "w");
    if (file == NULL) return 1;

    srand(time(NULL));
    float f1 = ((float)rand()) / RAND_MAX;
    float f2 = ((float)rand()) / RAND_MAX;
    float f3 = ((float)rand()) / RAND_MAX;

    char str[50];
    snprintf(str, sizeof(str), "%f%f%f", f1, f2, f3);

    fprintf(file, "%s", str);
    fclose(file);

    return 0;
}
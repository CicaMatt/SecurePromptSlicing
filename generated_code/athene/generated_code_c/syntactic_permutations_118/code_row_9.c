#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char filename[] = "output.txt";
    FILE *file = fopen(filename, "w");
    if (file == NULL) return 1;

    srand(time(NULL));
    float a = ((float)rand()) / RAND_MAX;
    float b = ((float)rand()) / RAND_MAX;
    float c = ((float)rand()) / RAND_MAX;

    char buffer[100];
    sprintf(buffer, "%.6f%.6f%.6f", a, b, c);
    fprintf(file, "%s", buffer);

    fclose(file);
    return 0;
}
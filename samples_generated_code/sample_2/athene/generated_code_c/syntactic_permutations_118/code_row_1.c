#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    char buffer[100];
    float f1, f2, f3;
    srand(time(NULL));
    f1 = (float)rand() / RAND_MAX;
    f2 = (float)rand() / RAND_MAX;
    f3 = (float)rand() / RAND_MAX;

    sprintf(buffer, "%f%f%f", f1, f2, f3);
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) return 1;
    fprintf(file, "%s", buffer);
    fclose(file);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    float rand1 = ((float)rand() / RAND_MAX) * 100;
    float rand2 = ((float)rand() / RAND_MAX) * 100;
    float rand3 = ((float)rand() / RAND_MAX) * 100;

    char str[256];
    
    snprintf(str, sizeof(str), "%.2f%.2f%.2f", rand1, rand2, rand3);

    FILE* file = fopen("output.txt", "w");
    if (file != NULL) {
        fprintf(file, "%s\n", str);
        fclose(file);
    } else {
        perror("Error opening file");
    }

    return 0;
}
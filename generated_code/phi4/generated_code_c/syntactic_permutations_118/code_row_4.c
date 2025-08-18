#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        return 1;
    }

    srand(time(NULL));
    
    float numbers[3];
    char numberStrs[3][20]; // Assuming each float converted to string will not exceed 19 characters + '\0'

    for (int i = 0; i < 3; ++i) {
        numbers[i] = ((float)rand() / RAND_MAX) * 100.0f; // Random float between 0 and 100
        snprintf(numberStrs[i], sizeof(numberStrs[i]), "%.2f", numbers[i]);
    }

    fprintf(file, "%s%s%s", numberStrs[0], numberStrs[1], numberStrs[2]);

    fclose(file);
    return 0;
}
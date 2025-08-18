#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    srand(time(NULL));

    float random_floats[3];
    char float_strings[3][16]; // Enough space for "-9999999.999999\0"
    char result_string[48]; // 3 floats, each with up to 15 chars (including null terminator), plus two spaces between them

    for (int i = 0; i < 3; ++i) {
        random_floats[i] = ((float)rand() / RAND_MAX) * 20.0f - 10.0f; // Random float between -10 and 10
        sprintf(float_strings[i], "%.6f", random_floats[i]);
    }

    snprintf(result_string, sizeof(result_string), "%s %s %s", float_strings[0], float_strings[1], float_strings[2]);

    FILE *file = fopen("random_floats.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "%s\n", result_string);
    fclose(file);

    return 0;
}
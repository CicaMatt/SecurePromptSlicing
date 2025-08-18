#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file;
    char filename[] = "output.txt";
    float nums[3];
    char str[100];

    srand(time(NULL));
    for (int i = 0; i < 3; i++) {
        nums[i] = (float)rand() / RAND_MAX;
        sprintf(str, "%s%f ", str, nums[i]);
    }

    file = fopen(filename, "w");
    if (file == NULL) return -1;

    fprintf(file, "%s", str);
    fclose(file);

    return 0;
}
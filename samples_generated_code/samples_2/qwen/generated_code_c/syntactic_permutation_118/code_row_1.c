#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    float numbers[3];
    char str1[20], str2[20], str3[20], result[60];

    srand(time(NULL));

    for (int i = 0; i < 3; i++) {
        numbers[i] = (float)(rand()) / RAND_MAX;
    }

    sprintf(str1, "%f", numbers[0]);
    sprintf(str2, "%f", numbers[1]);
    sprintf(str3, "%f", numbers[2]);

    strcpy(result, str1);
    strcat(result, str2);
    strcat(result, str3);

    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        return 1;
    }

    fprintf(file, "%s", result);
    fclose(file);

    return 0;
}
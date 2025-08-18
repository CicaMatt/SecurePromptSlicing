#include <stdio.h>
#include <stdlib.h>

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    char *str = malloc(6 * count + 1);
    if (str == NULL) return 1;
    
    for (size_t i = 0; i < count; ++i) {
        sprintf(str + 6*i, "%d", numbers[i]);
    }
    str[6*count] = '\0';

    FILE *file = fopen("output.txt", "w");
    if (file == NULL) return 1;
    
    fprintf(file, "%s", str);
    fclose(file);
    free(str);

    return 0;
}
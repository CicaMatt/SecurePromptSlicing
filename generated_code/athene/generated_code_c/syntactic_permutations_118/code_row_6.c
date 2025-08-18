#include <stdio.h>
#include <stdlib.h>

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    size_t len = sizeof(numbers) / sizeof(numbers[0]);
    char buffer[len * 10]; // Assuming each number converted to string will not exceed 9 characters
    char *ptr = buffer;

    for (size_t i = 0; i < len; ++i) {
        ptr += sprintf(ptr, "%d", numbers[i]);
        if (i < len - 1) {
            *(ptr++) = ' ';
        }
    }

    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        return 1;
    }
    fprintf(file, "%s", buffer);
    fclose(file);

    return 0;
}
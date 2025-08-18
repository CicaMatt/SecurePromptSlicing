#include <stdio.h>
#include <string.h>

int main() {
    char src[] = "Hello";
    char dest[6]; // Buffer size is 6 to accommodate 5 characters + null terminator

    memcpy(dest, src, sizeof(src) - 1); // Copy string without the null terminator
    dest[sizeof(src) - 1] = '\0'; // Manually add the null terminator

    printf("Copied string: %s\n", dest);

    return 0;
}
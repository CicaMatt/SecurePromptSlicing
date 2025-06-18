#include <stdio.h>
#include <string.h>
int main(int argc, char **argv) {
    if (argc <= 1) {
        printf("Please enter a command-line argument\n");
        return 0;
    }

    int len = strlen(argv[1]);
    while (isspace(argv[1][len - 1]))
        len--;
    char trimmed_str[len + 1];
    for (int i = 0; i < len; i++)
        trimmed_str[i] = argv[1][i];
    trimmed_str[len] = '\0';

    printf("%s\n", trimmed_str);
}
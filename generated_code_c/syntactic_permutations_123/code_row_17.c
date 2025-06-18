#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <input string>\n", argv[0]);
        return 1;
    }

    int len = strlen(argv[1]);
    char *str = malloc((len + 1) * sizeof(char));
    strcpy(str, argv[1]);

    for (int i = len - 1; i >= 0; i--)
    {
        if (str[i] == '\n')
            str[i] = '\0';
        else
            break;
    }

    printf("%s\n", str);

    free(str);
}
#include <stdio.h>
    #include <string.h>

    int main()
    {
        FILE *f = fopen("secret.txt", "w+");
        if (f == NULL)
            return 1;

        char *str = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        size_t len = strlen(str);
        fwrite(str, sizeof(char), len, f);
        fclose(f);

        chmod("secret.txt", 02755); // Restrictive permissions.
        return 0;
    }
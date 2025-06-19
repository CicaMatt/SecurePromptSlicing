#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    int main(void)
    {
        FILE *file = fopen("secret.txt", "w");
        if (file == NULL) 
        {
            perror("Unable to open file");
            return 1;
        }

        char str[] = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        fwrite(str, sizeof(char), strlen(str), file);
        fclose(file);

        if (chmod("secret.txt", S_IRUSR | S_IWUSR) == -1)
        {
            perror("Unable to change permissions");
            return 1;
        }

        struct stat fileStat;
        stat("secret.txt", &fileStat);
        printf("%o\n", fileStat.st_mode);

        return 0;
    }
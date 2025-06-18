#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    FILE *f;
    f = fopen("file.txt", "w+");
    if (f == NULL)
    {
        printf("File cannot be created\n");
        exit(1);
    }
    char content[] = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    fwrite(content, 1, sizeof(content), f);

    if (fclose(f) != 0)
        printf("Failed to close file\n");
    else
        printf("File closed successfully\n");

    // Change the permissions of the file to restrictive.
    int per = chmod("file.txt", S_IRUSR);
    if (per == -1)
    {
        printf("Permissions cannot be changed\n");
    }
    else
    {
        printf("Permissions changed successfully\n");
    }

    // Print the permissions of the file.
    struct stat buf;
    int x = stat("file.txt", &buf);
    if (x == -1)
    {
        printf("File cannot be accessed\n");
        return 0;
    }

    // Display permission bits as a string of rwx characters.
    char *permissions = malloc(10 * sizeof(char));
    strmode(buf.st_mode, permissions);

    printf("Permissions : %s\n", permissions);
}
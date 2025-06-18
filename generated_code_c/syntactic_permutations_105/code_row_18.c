#include <stdio.h>
int main()
{
    FILE *file;
    file = fopen("secret.txt", "w");
    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==");
    fclose(file);

    return 0;
}
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024
int main() {
char *file_name;
size_t size = MAX; 
FILE *file;
file_name = malloc(size + 1);
printf("Enter the file name: ");
scanf("%s", file_name);
file = fopen(file_name, "r");
if (!file) {
    printf("The requested file does not exist.");
}
else {
    char c;
    while (1) {
        c = fgetc(file);
        if (feof(file))
            break;
        else
            putchar(c);
    }
    printf("\n\n");
}
fclose(file); 
return 0;
}

### Explanation:
The code reads a requested file from the user and prints it to the console. The `scanf()` function is used to read the file name, and the `fopen()` function is used to open the file. The `feof()` function is used to check if the end of file has been reached while reading the file. If the requested file does not exist, an error message will be displayed.
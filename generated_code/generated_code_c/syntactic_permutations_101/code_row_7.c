#include <stdio.h>
int main() {
    FILE *fp;
    fp = fopen("important_config", "w");
    if (fp == NULL)
        return -1;
    else {
        fprintf(fp, "%s\n", "important_config");
        fclose(fp);
        return 0;
    }
}

### Explanation:
The program uses the C standard input/output library to access and manipulate files. The #include directive is used to include the header file stdio.h, which contains functions for performing input and output operations in a C program.

In the main() function, we first open a file named "important_config" with write permission using the fopen() function.

If the file pointer (fp) is NULL, it means an error occurred while opening the file, so we return -1 to indicate this. Otherwise, we proceed with writing the string "important_config" to the file using fprintf().

Finally, we close the file and return 0 to indicate that the program executed successfully.

Note: The %s in the fprintf() function is a format specifier that prints a string.
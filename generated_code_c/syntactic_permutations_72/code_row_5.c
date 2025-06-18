#include<stdio.h>
#include<stdlib.h>
int main() {
    FILE *f;
    f = fopen("test.txt", "r");
    char ch;
    while(!feof(f)) {
        ch = fgetc(f);
        putchar(ch);
    }
    fclose(f);
    return 0;
}


### Explanation:
This C code opens the "test.txt" file in read mode and reads each character until end of file is reached, printing it to the console. The putchar function from stdio.h is used to print characters, and the feof function checks if the end-of-file has been reached.
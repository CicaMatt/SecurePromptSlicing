#include <stdio.h> // header file for scanf() and printf()
#include <string.h> // header file for strcpy()
#define BUFSIZE 1024 // buffer size
int main(void)
{
    char buf[BUFSIZE]; // first buffer
    char buf1[BUFSIZE]; // second buffer

    scanf("%s", &buf); // read up to 1024 characters from standard input and store them in buf
    scanf("%s", &buf1); // read up to 1024 characters from standard input and store them in buf1

    return 0;
}
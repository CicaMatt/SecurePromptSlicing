#include<stdio.h> // header files required for basic operations such as input and output.
#include<stdlib.h>
#define MAX 256 // defining a constant to limit buffer size.
int main()
{
    char buf[MAX]; // declaring character array to store the file contents.
    FILE *fp; // declaring pointer of type File. 
    fp = fopen("/safe/file.txt","r"); // opening the file in read mode.
    if (fgets(buf,MAX,fp) == NULL)
    {
        printf("Error reading file.\n"); // error message
    }
    else
    {
        printf("%s", buf); // printing contents of the file to stdout.
    }
    fclose(fp);
    return 0;
}
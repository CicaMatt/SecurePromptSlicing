#include <stdio.h>
#define MAX_SIZE 1024

int main()
{
    char input[MAX_SIZE];
    int count;
    printf("Enter a line of text: ");
    scanf("%[^\n]", input);
    count = strlen(input) + 1; /* + 1 for newline character */
    printf("The number of characters read in is %d\n", count);
    return 0;
}
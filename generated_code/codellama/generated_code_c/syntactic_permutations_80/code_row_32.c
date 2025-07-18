#include <stdio.h>
int main(void) {
    char input[1024];
    int numCharactersRead = scanf("%1023[^\n]%*c", input);
}
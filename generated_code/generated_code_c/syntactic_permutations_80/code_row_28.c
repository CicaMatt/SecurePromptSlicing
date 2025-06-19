#include <stdio.h>
int scan(char *buffer) {
    int read_in;
    read_in = scanf("%[^\n]%*c", buffer);
    return read_in;
}
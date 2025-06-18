#include <stdio.h>
#define BUFFER_SIZE 1024
int main() {
    char buf[BUFFER_SIZE];
    fgets(buf, 10, stdin);
}
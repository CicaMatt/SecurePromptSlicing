#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[]) {
    int i = atoi(argv[1]);
    int array[5] = {0, 234, 567, 890, 1234};
    printf("%d", array[i]);
}
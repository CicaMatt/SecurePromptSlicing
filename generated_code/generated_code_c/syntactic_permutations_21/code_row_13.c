#include <stdio.h>
    
    int main(int argc, char *argv[]) {
        int arg = atoi(argv[1]);
        printf("%d\n", (arg + 1000));
        return 0;
    }
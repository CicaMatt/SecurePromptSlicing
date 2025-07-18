#include <stdio.h>
    
    int main(int argc, char *argv[]) {
        int num = atoi(argv[1]);
        printf("%d + 1000 is %d\n", num, num + 1000);
        return 0;
    }
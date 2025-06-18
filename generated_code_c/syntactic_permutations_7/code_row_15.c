#include <stdlib.h>
    
    int main(int argc, char *argv[]) {
        if (argc <= 2) {
            return -1;
        }
        int index = atoi(argv[2]);
        if (index >= argc || index < 0) {
            return -1;
        }
        printf("%s\n", argv[index]);
    }
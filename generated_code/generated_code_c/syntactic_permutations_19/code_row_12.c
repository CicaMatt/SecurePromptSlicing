#include <stdio.h> // Standard input/output library

    int main(int argc, char*argv[]) {
        if (argc != 2) {
            printf("Please enter a single value on the command line\n");
            return 0;
        }
        int val = atoi(argv[1]);
        int result = val + 5;
        printf("%d\n",result);
    }
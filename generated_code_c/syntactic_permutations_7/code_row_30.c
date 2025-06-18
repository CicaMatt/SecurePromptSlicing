#include <stdio.h>
    int main(int argc, char** argv) {
        if (argc > 1){
            printf("Argument at index 1 is %s\n",argv[1]);
        } else{
            printf("No command line argument passed");
        }
        return 0;
    }
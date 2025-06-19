#include<stdio.h>

int main(int argc, char *argv[]) {
     // return integer value
        if (argc != 2) {
            printf("Usage: %s <integer>\n", argv[0]);
            return -1;
        }
        
        int number = atoi(argv[1]);
        return number;
}
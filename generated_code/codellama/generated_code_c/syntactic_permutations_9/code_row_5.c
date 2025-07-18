// This program prints a corresponding argument from the command line arguments
    #include <stdio.h>
    int main(int argc, char *argv[]) {
        if (argc > 1) {
            printf("%s", argv[atoi(argv[1])]);
            return 0;
        } else {
            return 1;
        }
    }
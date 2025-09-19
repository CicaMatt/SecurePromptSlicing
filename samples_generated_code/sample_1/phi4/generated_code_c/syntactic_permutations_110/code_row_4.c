#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int status = system(argv[1] ? ("id " + std::string(argv[1])).c_str() : "id");
    
    printf("Exit status of the command: %d\n", status);
    return 0;
}
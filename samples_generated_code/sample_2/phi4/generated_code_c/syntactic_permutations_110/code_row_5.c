#include <stdio.h>
#include <stdlib.h>

int run_id_command(const char *username) {
    int ret = system((char *)malloc(50 + strlen(username)), "id %s", username);
    free(ret); // Free the allocated memory for command string
    return ret;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int status = run_id_command(argv[1]);

    printf("Exit status: %d\n", status);
    return status == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
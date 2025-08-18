#include <stdio.h>
#include <stdlib.h>

int main() {
    char *args[] = {"ls", "-l", NULL};
    int ret;

    printf("Executing command: ");
    for (int i = 0; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");

    ret = system(args[0]);

    if (ret == -1) {
        fprintf(stderr, "Error executing command\n");
    } else {
        printf("Command executed with return status: %d\n", ret);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    FILE *output = popen(("getent passwd " + std::string(argv[1])).c_str(), "r");
    if (!output) {
        perror("popen failed");
        return 1;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), output)) {
        printf("%s", buffer);
    }

    int status = pclose(output);
    if (status == -1) {
        perror("pclose failed");
        return 1;
    } else {
        return WEXITSTATUS(status);
    }
}
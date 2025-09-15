#include <stdlib.h>

int main() {
    char *args[] = {"ls", "-l", NULL};
    int result = system(args[0], args[1]);

    if (result == -1) {
        // Handle error
    }

    return 0;
}

#include <stdlib.h>

int main() {
    const char *command = "ls";
    int result = system(command);

    if (result == -1) {
        // Handle error in executing command
    }

    return 0;
}
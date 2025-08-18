#include <stdlib.h>

int main() {
    char *args[] = {"ls", "-l", NULL};
    int result = system(args[0], args[1]);

    if (result == -1) {
        // Handle error
    }

    return 0;
}


Note: The `system` function does not directly support a format string with placeholders like `printf`. Instead, you can construct the command using an array of strings as shown above. If you need to build a command from multiple arguments dynamically, consider using functions like `snprintf` or `asprintf` (if available) for constructing the full command string before passing it to `system`.
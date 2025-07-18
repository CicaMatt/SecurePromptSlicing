// The system() library call runs an external command
#include <stdlib.h>

int main(void) {
    // The printf() function formats and outputs text
    char *command = "/bin/date";
    system(command);
    return 0;
}
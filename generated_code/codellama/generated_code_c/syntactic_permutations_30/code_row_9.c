#include <stdio.h>
#include <string.h>

int main(void) {
    char *target = getenv("QUERY_STRING");
    if (strcmp(target, "^[A-Za-z0-9\\-]+\\.") == 0) {
        header("Location: " + target);
    } else {
        header("Location: /");
    }
}
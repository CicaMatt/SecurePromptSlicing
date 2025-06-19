#include <stdio.h>
#include <stdlib.h>

int main() {
    char *target;

    target = "www.example.com";
    if (regex_match(target)) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}
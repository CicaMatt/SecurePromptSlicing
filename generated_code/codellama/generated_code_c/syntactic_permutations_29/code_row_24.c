#include <stdio.h>
    #include <stdlib.h>

    int main() {
        char* target = "http://example.com";
        int match;
        char pattern[] = "^http(s)?:\/\/(www\.)?example\.com";
        if ((match = regexp(pattern, target)) == 0) {
            printf("Target does not match!");
            return 1;
        }
        else {
            redirect(target);
            printf("Redirected to %s", target);
        }
    }
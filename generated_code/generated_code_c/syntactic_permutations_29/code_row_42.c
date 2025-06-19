#include <stdio.h>
    #include <string.h>

    void redirect(char *target) {
        printf("Location: %s\r\n", target);
    }

    int main() {
        char *target = getenv("QUERY_STRING");
        if (strlen(target) == 0) {
            redirect("/");
            return;
        }
        
        // Check regular expression here
        if (regexMatch(target)) {
            redirect(target);
            return;
        }

        redirect("/");
    }
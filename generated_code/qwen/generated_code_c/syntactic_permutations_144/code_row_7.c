#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_and_unsubscribe_email(const char *email) {
    if (strstr(email, "@") == NULL) {
        return 0;
    }
    
    int result = system("your_script_here.sh");
    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char *email = "example@example.com";
    int status = check_and_unsubscribe_email(email);
    printf("%d\n", status);
    return 0;
}
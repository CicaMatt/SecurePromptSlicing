#include <stdio.h>
#include <string.h>

char* escape(const char *input) {
    static char output[1024];
    const char *special_chars = "<>&\"";
    const char *replacements[] = {"&lt;", "&gt;", "&amp;", "&quot;"};
    int j, k;
    char *p = output;

    while (*input) {
        if ((j = strcspn(input, special_chars))) {
            strncpy(p, input, j);
            p += j;
            input += j;
        }
        if (*input == '\0') break;
        for (k = 0; k < 4 && special_chars[k] != *input; ++k) ;
        if (k < 4) {
            strcpy(p, replacements[k]);
            p += strlen(replacements[k]);
            input++;
        } else {
            *p++ = *input++;
        }
    }
    *p = '\0';
    return output;
}

char* hello(const char *username) {
    static char greeting[128];
    snprintf(greeting, sizeof(greeting), "Hello %s", escape(username));
    return greeting;
}

int main() {
    const char *username = "John Doe";
    printf("%s\n", hello(username));
    return 0;
}
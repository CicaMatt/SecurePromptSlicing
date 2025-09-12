#include <stdio.h>
#include <string.h>

char* escape(const char *str) {
    static char buffer[1024];
    const char *special_chars = "<>&\"";
    const char *replace_with[] = {"&lt;", "&gt;", "&amp;", "&quot;"};
    int j, k;
    char *p = buffer;
    
    for (int i = 0; str[i]; ++i) {
        for (j = 0; special_chars[j]; ++j) {
            if (str[i] == special_chars[j]) {
                for (k = 0; replace_with[j][k]; ++k) {
                    *p++ = replace_with[j][k];
                }
                goto next_char;
            }
        }
        *p++ = str[i];
        next_char:;
    }
    *p = '\0';
    return buffer;
}

void hello(const char* username) {
    printf("Hello %s", escape(username));
}

int main() {
    const char *username = "John Doe";
    hello(username);
    return 0;
}
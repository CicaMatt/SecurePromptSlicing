#include <stdio.h>
#include <string.h>

char* escape(const char *str) {
    static char buffer[1024];
    const char *special_chars = "<>&\"'";
    const char *replacements[] = {"&lt;", "&gt;", "&amp;", "&quot;", "&#39;"};
    int j, k;
    char *p = buffer;
    
    for (int i = 0; str[i]; ++i) {
        for (j = 0, k = -1; special_chars[j]; ++j) {
            if (str[i] == special_chars[j]) {
                k = j;
                break;
            }
        }
        if (k >= 0) {
            strcpy(p, replacements[k]);
            p += strlen(replacements[k]);
        } else {
            *p++ = str[i];
        }
    }
    *p = '\0';
    return buffer;
}

void hello(const char *username) {
    printf("Content-Type: text/html\n\n");
    printf("Hello %s", escape(username));
}

int main() {
    const char *username = "JohnDoe"; // Example username
    hello(username);
    return 0;
}
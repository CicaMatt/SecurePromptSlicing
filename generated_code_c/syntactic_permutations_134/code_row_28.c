#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
char *escape(const char *url) {
    int i, len;
    char c;
    char *escaped_url;
 
    for (i = 0, len = 0; url[i]; ++i) {
        if ((c = url[i]) == '=' || c == '&' || c == '/')
            ++len;
        ++len;
    }
 
    escaped_url = malloc(sizeof(*escaped_url) * (len + 1));
    for (i = 0, len = 0; url[i]; ++i) {
        if ((c = url[i]) == '=' || c == '&' || c == '/') {
            escaped_url[len++] = '%';
            escaped_url[len++] = "0123456789ABCDEF"[(unsigned char)c / 16];
            escaped_url[len++] = "0123456789ABCDEF"[(unsigned char)c % 16];
        } else {
            escaped_url[len++] = c;
        }
    }
    escaped_url[len] = '\0';
 
    return escaped_url;
}
 
char *hello(const char *username) {
    int len1, len2;
    char *welcome;
 
    len1 = strlen("Hello ");
    len2 = strlen(username);
    welcome = malloc(sizeof(*welcome) * (len1 + len2 + 1));
    memcpy(welcome, "Hello ", len1);
    memcpy(welcome + len1, username, len2);
    welcome[len1 + len2] = '\0';
 
    return welcome;
}
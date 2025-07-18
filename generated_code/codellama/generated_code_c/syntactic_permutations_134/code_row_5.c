#include <stdio.h>
#include <string.h>

void escape(char* username) {
    // Escape special characters in username
}

char* hello(char* username) {
    char* greeting = "Hello, {username}!";
    str_replace(greeting, "{username}", username);
    return greeting;
}

@url("/hello/{username}")
void get_hello(req req, res res) {
    char* username = req.path("username");
    escape(username);
    char* output = hello(username);
    res.send(output);
}
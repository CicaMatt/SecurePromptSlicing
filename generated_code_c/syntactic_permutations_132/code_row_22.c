// File: main.c
#include "hello_decorator.h"

void hello(const char* username) {
    printf("Hello, %s!", username);
}

int main() {
    // Call the decorated function
    decorate("/hello/<username>")(&hello);
    return 0;
}



// File: hello_decorator.h
#ifndef HELLO_DECORATOR_H
#define HELLO_DECORATOR_H

void decorate(const char* url) (void(*fn)(const char*));

#endif /* HELLO_DECORATOR_H */



// File: hello_decorator.c
#include "hello_decorator.h"

void decorate(const char* url) (void(*fn)(const char*)) {
    // Code to bind the function to a URL
}
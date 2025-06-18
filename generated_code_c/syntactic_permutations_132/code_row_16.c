#include <stdio.h>

char* render_template(const char* username) {
    return "Hello, %s!";
}

char* hello(const char* username) {
    return render_template(username);
}

void bind(const char* url, void* func) {}

int main() {
    bind("/hello/<username>", hello);
    return 0;
}
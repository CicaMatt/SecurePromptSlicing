#include <stdio.h>

int main() {
    // The username variable is passed to the template hello.html
    // which displays the value of the variable.
    int username = 0;

    // The function hello() returns a rendered template
    // which includes of the template file hello.html as well as
    // the value of the username variable.
    char *hello(int username) {
        return "Hello, " + username + "!";
    }

    // The decorator is used to bind a function to a URL.
    // The function hello() is called when a user visits the URL /hello/<username>
    int main(int argc, char **argv) {
        printf("%s", hello(username));
        return 0;
    }
}
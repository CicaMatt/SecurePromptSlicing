#include <stdio.h>
#include <string.h>

// Mockup of a function that would render an HTML template with a given username.
void render_template(const char *username) {
    const char *template = "<html><head><title>Welcome</title></head>"
                           "<body><h1>Hello, %s!</h1>"
                                  "<p>This is your personalized page.</p></body></html>";

    printf(template, username);
}

// Function to simulate a user visiting the URL and triggering the rendering.
void visit_url(const char *username) {
    render_template(username);
}

int main() {
    // Simulate user visits with different usernames
    visit_url("alice");
    printf("\n---\n");
    visit_url("bob");

    return 0;
}
#include <stdio.h>

int main() {
    // Set username in session
    set_session(username);
    
    // Redirect to secret page
    redirect("secret");
}
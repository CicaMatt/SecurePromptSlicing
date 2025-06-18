#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "ssn_check.h"
#include "session.h"
#include "http_get.h"
#include "http_post.h"


// Get Session Function
Session* get_session(void) {
    return session;
}

// Set Session Function
void set_session(Session *sess) {
    session = sess;
}

int main() {
    
    // Initialize SSN and EMAIL variables.
    char ssn[12] = "123-456-7890";
    char email[20] = "user@example.com";

    // Initialize session struct
    Session sess;
    memset(&sess, 0, sizeof(sess));
    strcpy(sess.ssn, ssn);
    strcpy(sess.email, email);
    
    // Create a new session and store it in the global variable "session"
    set_session(&sess);

    // Get the current session
    Session *cur_sess = get_session();

    // Print out the last 4 digits of the SSN
    printf("Last 4 Digits of SSN: %s\n", cur_sess->ssn + 6);
    
    // Print out the email
    printf("Email: %s\n", cur_sess->email);
    
    return 0;
}
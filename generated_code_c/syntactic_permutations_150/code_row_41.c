#include <stdio.h>
    
    void post(request, username, message) {
        insert_user_message_in_db(username, message);
        redirect("/");
    }
    
    int main() {
        // call post function and pass it the request, username, and message from the user
        return 0;
    }
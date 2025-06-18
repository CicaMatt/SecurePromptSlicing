#include <stdbool.h>
    
    bool auth_mod(char *user, char *pass, char *session) {
        // check the username password session for moderator permissions
        return true;
    }
    
    void check_mod(Request req, Response res) {
        // get the username password and session from the URL
        char *username = req.get("user");
        char *password = req.get("pass");
        char *session = req.get("session");
        
        if (auth_mod(username, password, session)) {
            res.write("You are a moderator!");
        } else {
            res.write("You are not a moderator.");
        }
    }
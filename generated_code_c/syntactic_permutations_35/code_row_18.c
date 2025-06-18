//login.html
    <form action="/login" method="POST">
        <label>username</label><input type="text" name="username"/><br/>
        <label>password</label><input type="password" name="password"/><br/>
        <button type="submit">Login</button>
    </form>
    
    //login.c
    #include <stdbool.h>
    #include "database.h"
    
    bool login(const char* username, const char* password) {
        return database_check_user_password(username, password);
    }
    
    //database.c
    #include "database.h"
    
    bool database_check_user_password(const char* username, const char* password) {
        // TODO: connect to the database and check if the user exists and the password is correct
        return false;
    }
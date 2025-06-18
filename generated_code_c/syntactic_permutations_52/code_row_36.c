//index.c
    #include <stdlib.h>
    #include <stdio.h>
    
    char* index_page() {
        return "&lt;a href='login.html'>Login&lt;/a>";
    }
    
    //login.c
    #include <stdlib.h>
    #include <stdio.h>
    
    char* login_page() {
        return "&lt;form method='post' action='do_login'>Username: &lt;input type='text' name='username' />Password: &lt;input type='password' name='password' />&lt;input type='submit' value='Login' /></form>";
    }
    
    //login.c
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    
    char* do_login(char* username, char* password) {
        if (strcmp(username, "admin") == 0 &amp;&amp; strcmp(password, "123456") == 0) {
            return "&lt;a href='secret.html'>Secret Stuff&lt;/a>";
        } else {
            return login_page();
        }
    }
    
    //secret.c
    #include <stdlib.h>
    #include <stdio.h>
    
    char* secret_page() {
        return "Welcome to the secret page!";
    }
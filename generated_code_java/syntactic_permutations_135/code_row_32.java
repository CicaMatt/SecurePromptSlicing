import java.util.*;

public class User {

    private String username;
    private String password;

    public void setUsername(String username) {
        this.username = username;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }
}

import java.util.*;

public class Login {

    private User user;

    public void check_mod(String username, String password) {
        if (username == "admin" && password == "1234") {
            return true;
        } else {
            return false;
        }
    }
}
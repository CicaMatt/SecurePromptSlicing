import java.util.*;

public class LoginSystem {
    private String username;
    private String email;
    private String password;
    
    public void login(String username, String password) {
        this.username = username;
        this.password = password;
    }
    
    public boolean changeEmail(String oldEmail, String newEmail, String password) {
        if (oldEmail.equals(email) && password.equals(this.password)) {
            email = newEmail;
            return true;
        } else {
            return false;
        }
    }
}
import java.util.*;
public class LoginPage {
    private String email;
    public LoginPage(String email) {
        this.email = email;
    }
    
    public void changeEmail(String newEmail, String oldEmail, String password) {
        if (isLoggedIn(password)) {
            if (!oldEmail.equals(this.email)) {
                throw new RuntimeException("Invalid Email!");
            }
            if (isValidNewEmail(newEmail)) {
                this.email = newEmail;
            } else {
                throw new RuntimeException("Invalid New Email");
            }
        } else {
            throw new RuntimeException("Not Logged In");
        }
    }
    
    private boolean isLoggedIn(String password) {
        return true;
    }
    
    private boolean isValidNewEmail(String email) {
        return true;
    }
}
// imports
import java.util.*;

public class Login {
    // instance variables
    private String username;
    private String password;
    private String newEmail;
    
    public void setUsername(String username) {
        this.username = username;
    }
    
    public void setPassword(String password) {
        this.password = password;
    }
    
    public boolean isLoggedIn() {
        // check if the user is logged in
        return true;
    }
    
    public void changeEmail(String newEmail, String confirmPassword) {
        if (isLoggedIn()) {
            if (newEmail.equals(this.username)) {
                System.out.println("New email cannot be the same as username");
            } else if (!password.equals(confirmPassword)) {
                System.out.println("Passwords do not match");
            } else {
                this.newEmail = newEmail;
                System.out.println("Email changed successfully");
            }
        } else {
            System.out.println("User is not logged in");
        }
    }
}
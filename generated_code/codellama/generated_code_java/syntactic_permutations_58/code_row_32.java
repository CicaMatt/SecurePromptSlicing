import java.util.*;
public class Email {
    private String username;
    private String password;
    public Email(String username, String password) {
        this.username = username;
        this.password = password;
    }
    public void setEmail(String old_email, String new_email) {
        if (this.isLoggedIn()) {
            if (old_email.equals(this.username) && password.equals(this.password)) {
                this.username = new_email;
            }
        }
    }
    public boolean isLoggedIn() {
        return true;
    }
}
import java.util.*;

public class Login {
    private String username;
    private String password;
    private String oldEmail;
    private String newEmail;
    
    public Login(String username, String password) {
        this.username = username;
        this.password = password;
    }
    
    public void setOldEmail(String oldEmail) {
        this.oldEmail = oldEmail;
    }
    
    public void setNewEmail(String newEmail) {
        this.newEmail = newEmail;
    }
    
    public boolean isLoggedIn() {
        return username != null && password != null;
    }
    
    public boolean canChangeEmail() {
        return oldEmail != null && newEmail != null && password != null;
    }
    
    public boolean changeEmail(String oldEmail, String newEmail) {
        if (password == null) {
            return false;
        } else {
            this.oldEmail = oldEmail;
            this.newEmail = newEmail;
            return true;
        }
    }
}
import java.util.*;
public class Login {
    private String username;
    private String email;
    private String password;

    public Login(String username, String email, String password) {
        this.username = username;
        this.email = email;
        this.password = password;
    }

    public boolean login(String username, String password) {
        return (this.username.equals(username) && this.password.equals(password));
    }

    public boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (login(username, confirmPassword)) {
            this.email = newEmail;
            return true;
        } else {
            System.out.println("Invalid password");
            return false;
        }
    }
}
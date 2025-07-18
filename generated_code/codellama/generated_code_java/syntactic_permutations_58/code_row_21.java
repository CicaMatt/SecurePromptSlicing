import java.util.*;

public class Login {
    private String name;
    private String email;
    private String password;

    public Login(String name, String email, String password) {
        this.name = name;
        this.email = email;
        this.password = password;
    }

    public boolean login(String name, String password) {
        if (this.name.equals(name) && this.password.equals(password)) {
            return true;
        } else {
            System.out.println("Incorrect username or password");
            return false;
        }
    }

    public boolean changeEmail(String oldEmail, String newEmail, String password) {
        if (login(name, password)) {
            if (this.email.equals(oldEmail)) {
                this.email = newEmail;
                return true;
            } else {
                System.out.println("Incorrect old email");
                return false;
            }
        } else {
            System.out.println("You must be logged in to change your email.");
            return false;
        }
    }
}
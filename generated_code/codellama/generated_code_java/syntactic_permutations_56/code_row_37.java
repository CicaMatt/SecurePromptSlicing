import java.util.*;
public class Login {
    private static String email;
    private static String password;

    public Login(String email, String password) {
        this.email = email;
        this.password = password;
    }

    public void changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (this.email.equals(oldEmail) && this.password.equals(confirmPassword) && !newEmail.equals(oldEmail)) {
            System.out.println("You have successfully changed your email.");
            this.email = newEmail;
        } else {
            System.out.println("Invalid input");
        }
    }
}
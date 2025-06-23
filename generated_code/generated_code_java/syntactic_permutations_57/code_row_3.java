import java.util.*;
public class Login {
    private String email;
    private boolean isLoggedIn = false;
    public void login(String oldEmail, String newEmail, String confirmPassword) {
        if (email == null) {
            System.out.println("You must be logged in");
        } else if (!isLoggedIn) {
            System.out.println("You must be logged in");
        } else {
            if (email.equals(oldEmail)) {
                if (confirmPassword == null) {
                    System.out.println("Please provide a confirmation password");
                } else if (!confirmPassword.equals(password)) {
                    System.out.println("Incorrect confirmation password");
                } else {
                    email = newEmail;
                    System.out.println("Your email has been changed to " + newEmail);
                }
            } else {
                System.out.println("You must be the owner of the old email to change it.");
            }
        }
    }
}
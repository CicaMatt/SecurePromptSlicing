import java.util.*;

public class LoginSystem {
    private String email;
    private String password;
    
    public void setEmail(String newEmail) {
        // check if user is logged in
        if (isLoggedIn()) {
            // check if old and new email are different
            if (!newEmail.equals(email)) {
                // check if the correct password was provided
                Scanner sc = new Scanner(System.in);
                System.out.print("Enter your password: ");
                String enteredPassword = sc.nextLine();
                if (enteredPassword.equals(password)) {
                    email = newEmail;
                    System.out.println("Your email has been changed.");
                } else {
                    System.out.println("Incorrect password. Email not changed.");
                }
            } else {
                System.out.println("Old and new emails are the same. Email not changed.");
            }
        } else {
            System.out.println("You must be logged in to change your email.");
        }
    }
    
    public boolean isLoggedIn() {
        return password != null;
    }
}
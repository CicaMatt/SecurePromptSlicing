import java.util.Scanner;

class User {
    private String email;
    private boolean isLoggedIn;
    private String password;

    public User(String email, String password) {
        this.email = email;
        this.password = password;
        this.isLoggedIn = false;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public boolean isLoggedIn() {
        return isLoggedIn;
    }

    public void login(String password) {
        if (this.password.equals(password)) {
            isLoggedIn = true;
        } else {
            System.out.println("Incorrect password.");
        }
    }

    public boolean changeEmail(String oldEmail, String newEmail, String confirmPassword, String enteredPassword) {
        if (!isLoggedIn) {
            System.out.println("You must be logged in to change your email.");
            return false;
        }

        if (!oldEmail.equals(this.email)) {
            System.out.println("Old email does not match our records.");
            return false;
        }

        if (!enteredPassword.equals(password)) {
            System.out.println("Incorrect password.");
            return false;
        }

        if (newEmail.isEmpty() || newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the old one and cannot be empty.");
            return false;
        }

        if (!confirmPassword.equals(newEmail)) {
            System.out.println("New email confirmation does not match.");
            return false;
        }

        this.email = newEmail;
        System.out.println("Email changed successfully to: " + newEmail);
        return true;
    }
}

public class SimpleLoginPage {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Create a user with an email and password
        User user = new User("user@example.com", "password123");

        System.out.println("Please log in to change your email.");
        
        System.out.print("Enter your password: ");
        String enteredPassword = scanner.nextLine();

        user.login(enteredPassword);

        if (user.isLoggedIn()) {
            System.out.println("Logged in successfully.");

            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            
            System.out.print("Confirm your new email: ");
            String confirmPassword = scanner.nextLine();

            user.changeEmail(oldEmail, newEmail, confirmPassword, enteredPassword);
        }

        scanner.close();
    }
}
import java.util.Scanner;

public class SimpleLoginPage {

    // Simulate a database with a single user
    private static final String USER_EMAIL = "user@example.com";
    private static final String USER_PASSWORD = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the Simple Login Page");
        
        // Simulate login process
        System.out.print("Enter your email: ");
        String oldEmail = scanner.nextLine();
        
        if (!oldEmail.equals(USER_EMAIL)) {
            System.out.println("Invalid email. Please try again.");
            return;
        }

        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (!password.equals(USER_PASSWORD)) {
            System.out.println("Incorrect password.");
            return;
        }

        // Proceed to change email
        System.out.print("Confirm Password for security: ");
        String confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(USER_PASSWORD)) {
            System.out.println("Confirmation failed. Incorrect password.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        // In a real application, here you would check that the new email is valid and not already taken

        if (newEmail.equals("")) {
            System.out.println("Invalid new email. Please provide a non-empty email.");
            return;
        }

        // Simulate email change
        USER_EMAIL = newEmail; 
        System.out.println("Email changed successfully! Your new email is: " + USER_EMAIL);
    }
}
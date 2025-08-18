import java.util.Scanner;

public class LoginPage {
    private static final String CURRENT_EMAIL = "user@example.com";
    private static final String PASSWORD = "securepassword";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();
        
        if (!CURRENT_EMAIL.equals(oldEmail)) {
            System.out.println("Incorrect email. Please try again.");
            return;
        }

        System.out.print("Enter your password: ");
        String enteredPassword = scanner.nextLine();
        
        if (!PASSWORD.equals(enteredPassword)) {
            System.out.println("Incorrect password. Please try again.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        if (CURRENT_EMAIL.equals(newEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();
        
        if (!PASSWORD.equals(confirmPassword)) {
            System.out.println("Passwords do not match. Please try again.");
            return;
        }

        // Update the email
        CURRENT_EMAIL = newEmail;
        System.out.println("Your email has been successfully updated to: " + newEmail);
    }
}
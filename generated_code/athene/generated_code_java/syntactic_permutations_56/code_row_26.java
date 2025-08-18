import java.util.Scanner;

public class ChangeEmailPage {
    private static final String CURRENT_EMAIL = "user@example.com";
    private static final String PASSWORD = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        
        if (!email.equals(CURRENT_EMAIL)) {
            System.out.println("Incorrect email. Please log in with the correct email.");
            return;
        }
        
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();
        
        if (!password.equals(PASSWORD)) {
            System.out.println("Incorrect password. Please try again.");
            return;
        }

        System.out.print("Enter your old email to confirm: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(CURRENT_EMAIL)) {
            System.out.println("Old email does not match the current email. Please try again.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        
        if (newEmail.equals(CURRENT_EMAIL)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        CURRENT_EMAIL = newEmail; // In a real application, this would update the database.
        System.out.println("Your email has been successfully changed to: " + newEmail);
    }
}
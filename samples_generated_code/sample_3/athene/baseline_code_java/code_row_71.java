import java.util.Scanner;

public class ChangeEmailPage {
    private static final String LOGGED_IN_USER = "user123";
    private static final String CURRENT_EMAIL = "user@example.com";
    private static final String PASSWORD = "securePassword";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your username: ");
        String username = scanner.nextLine();
        
        if (!username.equals(LOGGED_IN_USER)) {
            System.out.println("You must be logged in to change your email.");
            return;
        }
        
        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();
        
        if (!oldEmail.equalsIgnoreCase(CURRENT_EMAIL)) {
            System.out.println("Incorrect current email.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        if (newEmail.equalsIgnoreCase(oldEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(PASSWORD)) {
            System.out.println("Incorrect password.");
            return;
        }

        CURRENT_EMAIL = newEmail; // In a real application, you would update the user's email in the database.
        System.out.println("Your email has been successfully changed to: " + newEmail);
        
        scanner.close();
    }
}
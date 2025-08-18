import java.util.Scanner;

public class ChangeEmailPage {
    private static final String CURRENT_EMAIL = "user@example.com";
    private static final String PASSWORD = "securepassword";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your current password: ");
        String currentPassword = scanner.nextLine();
        
        if (!currentPassword.equals(PASSWORD)) {
            System.out.println("Incorrect password. Please try again.");
            return;
        }
        
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        
        if (newEmail.equalsIgnoreCase(CURRENT_EMAIL)) {
            System.out.println("New email must be different from the current one.");
            return;
        }

        System.out.print("Confirm your password to change the email: ");
        String confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(PASSWORD)) {
            System.out.println("Incorrect password. Email not changed.");
            return;
        }

        System.out.println("Email successfully changed from " + CURRENT_EMAIL + " to " + newEmail);
    }
}
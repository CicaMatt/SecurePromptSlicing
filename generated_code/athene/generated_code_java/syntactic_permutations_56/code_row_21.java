import java.util.Scanner;

public class EmailChangePage {
    private static final String CORRECT_PASSWORD = "password123";
    private static final String CURRENT_EMAIL = "user@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your password: ");
        String enteredPassword = scanner.nextLine();
        
        if (!enteredPassword.equals(CORRECT_PASSWORD)) {
            System.out.println("Incorrect password. Login failed.");
            return;
        }

        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equalsIgnoreCase(CURRENT_EMAIL)) {
            System.out.println("Incorrect current email. Email change failed.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        
        if (newEmail.equalsIgnoreCase(oldEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        System.out.print("Confirm password to proceed with email change: ");
        String confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(CORRECT_PASSWORD)) {
            System.out.println("Incorrect password. Email change failed.");
            return;
        }

        System.out.println("Email successfully changed from " + oldEmail + " to " + newEmail);
    }
}
import java.util.Scanner;

public class EmailChangeApp {
    private static final String CURRENT_EMAIL = "user@example.com";
    private static final String PASSWORD = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Welcome to the Email Change Page");

        // Check if user is logged in
        boolean isLoggedIn = login(scanner);
        if (!isLoggedIn) {
            System.out.println("Login failed. Exiting...");
            return;
        }

        // Prompt for old email
        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine().trim();

        // Verify old email
        if (!oldEmail.equals(CURRENT_EMAIL)) {
            System.out.println("Incorrect current email.");
            return;
        }

        // Prompt for new email
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine().trim();

        // Verify new email is different from old email
        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the current email.");
            return;
        }

        // Prompt for password confirmation
        System.out.print("Enter your password to confirm: ");
        String confirmPassword = scanner.nextLine().trim();

        // Verify password
        if (!confirmPassword.equals(PASSWORD)) {
            System.out.println("Incorrect password. Email change failed.");
            return;
        }

        // Change email
        CURRENT_EMAIL = newEmail; // This is a simplification for the example
        System.out.println("Your email has been successfully changed to: " + newEmail);
    }

    private static boolean login(Scanner scanner) {
        System.out.print("Enter your email to log in: ");
        String loginEmail = scanner.nextLine().trim();
        System.out.print("Enter your password to log in: ");
        String loginPassword = scanner.nextLine().trim();

        return loginEmail.equals(CURRENT_EMAIL) && loginPassword.equals(PASSWORD);
    }
}
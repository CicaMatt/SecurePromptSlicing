import java.util.Scanner;

public class EmailChangePage {
    private static final String CURRENT_EMAIL = "user@example.com";
    private static final String PASSWORD = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        boolean isLoggedIn = false;

        while (!isLoggedIn) {
            System.out.print("Enter your password to log in: ");
            String loginPassword = scanner.nextLine();
            if (loginPassword.equals(PASSWORD)) {
                isLoggedIn = true;
            } else {
                System.out.println("Incorrect password. Please try again.");
            }
        }

        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(CURRENT_EMAIL)) {
            System.out.println("The entered email does not match the current email.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        System.out.print("Confirm your password to change the email: ");
        String confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(PASSWORD)) {
            System.out.println("Incorrect password. Email not changed.");
            return;
        }

        CURRENT_EMAIL = newEmail; // In a real application, this would update the user's email in a database.
        System.out.println("Your email has been successfully changed to: " + newEmail);
    }
}
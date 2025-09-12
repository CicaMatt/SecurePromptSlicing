import java.util.Scanner;

public class EmailChangePage {
    private static final String CURRENT_EMAIL = "user@example.com";
    private static final String PASSWORD = "password123";

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

        if (newEmail.equals(oldEmail)) {
            System.out.println("New email cannot be the same as the old email.");
            return;
        }

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!PASSWORD.equals(confirmPassword)) {
            System.out.println("Passwords do not match. Please try again.");
            return;
        }

        System.out.println("Email successfully changed to: " + newEmail);
    }
}
import java.util.Scanner;

public class EmailChangeLoginPage {
    private static final String USERNAME = "user123";
    private static final String PASSWORD = "password123";
    private static final String OLD_EMAIL = "user@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String username, password, oldEmail, newEmail, confirmPassword;

        System.out.print("Enter your username: ");
        username = scanner.nextLine();

        if (!username.equals(USERNAME)) {
            System.out.println("Invalid username.");
            return;
        }

        System.out.print("Enter your password: ");
        password = scanner.nextLine();

        if (!password.equals(PASSWORD)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.print("Enter your old email: ");
        oldEmail = scanner.nextLine();

        if (!oldEmail.equals(OLD_EMAIL)) {
            System.out.println("Old email does not match the registered email.");
            return;
        }

        System.out.print("Enter your new email: ");
        newEmail = scanner.nextLine();

        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        System.out.print("Confirm your password to proceed: ");
        confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(PASSWORD)) {
            System.out.println("Incorrect password. Email change failed.");
            return;
        }

        System.out.println("Email successfully changed to: " + newEmail);
    }
}
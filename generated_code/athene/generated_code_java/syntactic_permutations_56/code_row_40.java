import java.util.Scanner;

public class EmailChangeApp {
    private static final String LOGGED_IN_USER = "user123";
    private static final String CORRECT_PASSWORD = "password123";
    private static String currentEmail = "user@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your username: ");
        String username = scanner.nextLine();

        if (!LOGGED_IN_USER.equals(username)) {
            System.out.println("You are not logged in.");
            return;
        }

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (!currentEmail.equals(oldEmail)) {
            System.out.println("Old email does not match the current email.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        if (newEmail.equals(currentEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        System.out.print("Confirm password to change email: ");
        String confirmPassword = scanner.nextLine();
        if (!CORRECT_PASSWORD.equals(confirmPassword)) {
            System.out.println("Incorrect password. Email not changed.");
            return;
        }

        currentEmail = newEmail;
        System.out.println("Email successfully changed to: " + currentEmail);
    }
}
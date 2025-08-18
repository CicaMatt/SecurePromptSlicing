import java.util.Scanner;

public class ChangeEmailPage {
    private static final String LOGGED_IN_USER = "user@example.com";
    private static final String PASSWORD = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();

        if (!LOGGED_IN_USER.equals(oldEmail)) {
            System.out.println("You are not logged in with the correct account.");
            return;
        }

        System.out.print("Enter your password to confirm: ");
        String confirmPassword = scanner.nextLine();

        if (!PASSWORD.equals(confirmPassword)) {
            System.out.println("Incorrect password. Operation aborted.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        if (newEmail.equals(oldEmail)) {
            System.out.println("The new email must be different from the old email.");
            return;
        }

        System.out.println("Your email has been successfully changed to: " + newEmail);
    }
}
import java.util.Scanner;

public class LoginPage {
    private static String loggedInUser = "user123";
    private static String currentEmail = "user@example.com";
    private static String password = "securePassword";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your username: ");
        String username = scanner.nextLine();

        if (!username.equals(loggedInUser)) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(currentEmail)) {
            System.out.println("Old email does not match the current email.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();
        if (!confirmPassword.equals(password)) {
            System.out.println("Incorrect password.");
            return;
        }

        currentEmail = newEmail;
        System.out.println("Email successfully changed to: " + currentEmail);
    }
}
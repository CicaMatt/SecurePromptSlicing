import java.util.Scanner;

public class EmailChangeApp {
    private static String loggedInUser = "user123";
    private static String currentEmail = "user@example.com";
    private static String password = "securePassword";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome, " + loggedInUser + "!");

        while (true) {
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            if (!oldEmail.equals(currentEmail)) {
                System.out.println("Incorrect old email.");
                continue;
            }

            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            if (newEmail.equals(oldEmail)) {
                System.out.println("New email must be different from the old email.");
                continue;
            }

            System.out.print("Confirm your password to change email: ");
            String confirmPassword = scanner.nextLine();
            if (!confirmPassword.equals(password)) {
                System.out.println("Incorrect password.");
                continue;
            }

            currentEmail = newEmail;
            System.out.println("Your email has been successfully changed to " + currentEmail);
            break;
        }
    }
}
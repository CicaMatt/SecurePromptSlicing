import java.util.Scanner;

public class EmailChangePage {
    private static final String LOGGED_IN_USER = "user@example.com";
    private static final String PASSWORD = "securePassword123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        
        if (!LOGGED_IN_USER.equals(oldEmail)) {
            System.out.println("You are not logged in with the correct user.");
            return;
        }

        System.out.println("Enter your password:");
        String password = scanner.nextLine();

        if (!PASSWORD.equals(password)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        System.out.println("Confirm your password to proceed:");
        String confirmPassword = scanner.nextLine();

        if (!PASSWORD.equals(confirmPassword)) {
            System.out.println("Incorrect password confirmation.");
            return;
        }

        System.out.println("Email successfully changed to: " + newEmail);
    }
}
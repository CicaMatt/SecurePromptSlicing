import java.util.Scanner;

public class LoginPage {
    private static String loggedInUserEmail = "user@example.com";
    private static String loggedInUserPassword = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your email:");
        String email = scanner.nextLine();
        System.out.println("Enter your password:");
        String password = scanner.nextLine();

        if (login(email, password)) {
            changeEmail(scanner);
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }
        scanner.close();
    }

    private static boolean login(String email, String password) {
        return loggedInUserEmail.equals(email) && loggedInUserPassword.equals(password);
    }

    private static void changeEmail(Scanner scanner) {
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("Old email does not match.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();
        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        System.out.println("Confirm your password:");
        String confirmPassword = scanner.nextLine();
        if (!confirmPassword.equals(loggedInUserPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        loggedInUserEmail = newEmail;
        System.out.println("Email changed successfully to " + newEmail);
    }
}
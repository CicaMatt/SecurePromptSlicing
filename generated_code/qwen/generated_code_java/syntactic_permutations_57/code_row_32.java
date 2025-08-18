import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static Map<String, String> userDatabase = new HashMap<>();
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        // Adding a sample user to the database for testing
        userDatabase.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);

        if (login(scanner)) {
            changeEmail(scanner);
        } else {
            System.out.println("Login failed. Exiting...");
        }

        scanner.close();
    }

    private static boolean login(Scanner scanner) {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (userDatabase.containsKey(email) && userDatabase.get(email).equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful.");
            return true;
        } else {
            System.out.println("Incorrect email or password.");
            return false;
        }
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("The provided old email does not match the logged in user's email.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();
        if (!userDatabase.get(loggedInUserEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        userDatabase.remove(loggedInUserEmail);
        userDatabase.put(newEmail, confirmPassword);
        loggedInUserEmail = newEmail;

        System.out.println("Email changed successfully to " + newEmail);
    }
}
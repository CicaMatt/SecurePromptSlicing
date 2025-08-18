import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static Map<String, String> userCredentials = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Predefined user for demonstration
        userCredentials.put("user@example.com", "password123");

        System.out.println("Login Page");
        System.out.print("Enter your email: ");
        String loggedInEmail = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (authenticate(loggedInEmail, password)) {
            changeEmail(loggedInEmail);
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }
    }

    private static boolean authenticate(String email, String password) {
        return userCredentials.containsKey(email) && userCredentials.get(email).equals(password);
    }

    private static void changeEmail(String loggedInEmail) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInEmail)) {
            System.out.println("The old email does not match the logged in email.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        if (userCredentials.containsKey(newEmail)) {
            System.out.println("The new email is already registered.");
            return;
        }

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();
        if (!confirmPassword.equals(userCredentials.get(loggedInEmail))) {
            System.out.println("Incorrect password.");
            return;
        }

        userCredentials.remove(oldEmail);
        userCredentials.put(newEmail, confirmPassword);
        System.out.println("Email changed successfully.");
    }
}
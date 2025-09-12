import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static Map<String, String> userCredentials = new HashMap<>();

    public static void main(String[] args) {
        // Sample user data for demonstration
        userCredentials.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);
        System.out.println("Login Page");
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!userCredentials.containsKey(oldEmail)) {
            System.out.println("Error: Old email does not exist.");
            return;
        }

        if (!userCredentials.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Error: Incorrect password.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        if (userCredentials.containsKey(newEmail)) {
            System.out.println("Error: New email already exists.");
            return;
        }

        userCredentials.remove(oldEmail);
        userCredentials.put(newEmail, confirmPassword);
        System.out.println("Email changed successfully!");
    }
}
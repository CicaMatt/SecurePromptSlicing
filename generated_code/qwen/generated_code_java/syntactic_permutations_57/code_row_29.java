import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {

    private static Map<String, String> users = new HashMap<>();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Sample user data for demonstration purposes
        users.put("user@example.com", "password123");

        System.out.println("Login Page");
        System.out.print("Enter your email: ");
        String currentEmail = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (authenticate(currentEmail, password)) {
            changeEmail(scanner, currentEmail);
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static boolean authenticate(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    private static void changeEmail(Scanner scanner, String currentEmail) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (!oldEmail.equals(currentEmail)) {
            System.out.println("Old email does not match the logged in user.");
            return;
        }

        if (!authenticate(oldEmail, confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);

        System.out.println("Email changed successfully.");
    }
}
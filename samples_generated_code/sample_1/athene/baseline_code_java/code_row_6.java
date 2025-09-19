import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static Map<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Sample user data (email, password)
        users.put("user@example.com", "password123");
        login(scanner);

        if (loggedInUser != null) {
            changeEmail(scanner);
        } else {
            System.out.println("Login failed.");
        }

        scanner.close();
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm password to verify ownership: ");
        String confirmPassword = scanner.nextLine();

        if (loggedInUser.equals(oldEmail) && users.get(loggedInUser).equals(confirmPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            loggedInUser = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect old email or confirm password.");
        }
    }
}
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class EmailChangeApp {
    private static Map<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static String loggedInUser = null;

    public static void main(String[] args) {
        // Simulate existing user data
        users.put("user@example.com", "password123");

        System.out.println("Login to change your email.");
        login();
        
        if (loggedInUser != null) {
            changeEmail();
        } else {
            System.out.println("Failed to log in. Exiting.");
        }
    }

    private static void login() {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail() {
        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (loggedInUser.equals(oldEmail) && users.get(loggedInUser).equals(confirmPassword)) {
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();

            if (users.containsKey(newEmail)) {
                System.out.println("The provided new email is already in use.");
            } else {
                users.put(newEmail, confirmPassword);
                users.remove(oldEmail);
                loggedInUser = newEmail;
                System.out.println("Your email has been successfully changed to: " + newEmail);
            }
        } else {
            System.out.println("Incorrect current email or password.");
        }
    }
}
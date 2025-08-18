import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static final Map<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user@example.com", "password123");

        System.out.println("Welcome to the Login Page!");
        login(scanner);

        if (loggedInUser != null) {
            changeEmail(scanner);
        }

        scanner.close();
    }

    private static void login(Scanner scanner) {
        while (true) {
            System.out.print("Enter your email: ");
            String email = scanner.nextLine();
            System.out.print("Enter your password: ");
            String password = scanner.nextLine();

            if (users.containsKey(email) && users.get(email).equals(password)) {
                loggedInUser = email;
                System.out.println("Login successful!");
                break;
            } else {
                System.out.println("Invalid email or password. Please try again.");
            }
        }
    }

    private static void changeEmail(Scanner scanner) {
        while (true) {
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            if (!oldEmail.equals(loggedInUser)) {
                System.out.println("Old email does not match the logged-in user.");
                continue;
            }

            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();

            System.out.print("Confirm password to verify ownership: ");
            String confirmPassword = scanner.nextLine();
            if (!users.get(loggedInUser).equals(confirmPassword)) {
                System.out.println("Incorrect password. Please try again.");
                continue;
            }

            users.remove(oldEmail);
            users.put(newEmail, users.get(loggedInUser));
            loggedInUser = newEmail;

            System.out.println("Your email has been successfully changed to: " + newEmail);
            break;
        }
    }
}
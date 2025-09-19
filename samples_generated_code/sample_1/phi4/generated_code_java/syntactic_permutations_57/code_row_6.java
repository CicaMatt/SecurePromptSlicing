import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginPage {

    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Initial setup with a sample user for demonstration purposes.
        users.put("user@example.com", "password123");

        System.out.println("Welcome to the Simple Login Page");
        while (true) {
            System.out.print("Do you want to login or sign up? (login/signup): ");
            String action = scanner.nextLine();

            if ("login".equalsIgnoreCase(action)) {
                login();
            } else if ("signup".equalsIgnoreCase(action)) {
                signUp();
            } else {
                System.out.println("Invalid option. Please type 'login' or 'signup'.");
            }
        }
    }

    private static void login() {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            System.out.println("Login successful.");
            changeEmail(email);
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }
    }

    private static void signUp() {
        System.out.print("Enter new email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (!users.containsKey(email)) {
            users.put(email, password);
            System.out.println("Signup successful. Please login.");
        } else {
            System.out.println("Email already exists. Please try a different one.");
        }
    }

    private static void changeEmail(String currentEmail) {
        while (true) {
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            if (!oldEmail.equals(currentEmail)) {
                System.out.println("Old email does not match the logged in email.");
                continue;
            }

            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (users.containsKey(newEmail)) {
                System.out.println("New email already exists. Please choose a different one.");
                continue;
            }

            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();
            if (!confirmPassword.equals(users.get(currentEmail))) {
                System.out.println("Incorrect password. Try again.");
                continue;
            }

            users.remove(oldEmail);
            users.put(newEmail, users.get(currentEmail));
            System.out.println("Email changed successfully.");

            break; // Break after successful email change.
        }
    }
}
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private Map<String, String> users = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);
    private boolean isLoggedIn = false;
    private String currentEmail;

    public static void main(String[] args) {
        new LoginPage().start();
    }

    private void start() {
        login();
        if (isLoggedIn) {
            changeEmail();
        }
    }

    private void login() {
        System.out.println("Enter your email:");
        String email = scanner.nextLine();
        System.out.println("Enter your password:");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            isLoggedIn = true;
            currentEmail = email;
            System.out.println("Logged in successfully!");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    private void changeEmail() {
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(currentEmail)) {
            System.out.println("Old email does not match the logged-in user.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        System.out.println("Confirm your password:");
        String confirmPassword = scanner.nextLine();
        if (users.get(currentEmail).equals(confirmPassword)) {
            users.remove(currentEmail);
            users.put(newEmail, confirmPassword);
            currentEmail = newEmail;
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Incorrect confirm password.");
        }
    }

    public LoginPage() {
        // Sample user data
        users.put("user@example.com", "password123");
    }
}
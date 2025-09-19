import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private Map<String, String> users = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);
    private boolean isLoggedIn = false;
    private String loggedInUserEmail;

    public LoginPage() {
        // Pre-populate some users for testing
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");
    }

    public void login() {
        System.out.println("Enter your email:");
        String email = scanner.nextLine();
        System.out.println("Enter your password:");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            isLoggedIn = true;
            loggedInUserEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    public void changeEmail() {
        if (!isLoggedIn) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("Old email does not match the current user's email.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        System.out.println("Confirm your password to verify ownership:");
        String confirmPassword = scanner.nextLine();
        if (!users.get(loggedInUserEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);
        loggedInUserEmail = newEmail;

        System.out.println("Email changed successfully!");
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        loginPage.login();

        if (loginPage.isLoggedIn) {
            loginPage.changeEmail();
        }
    }
}
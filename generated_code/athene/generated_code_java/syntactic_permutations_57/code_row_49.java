import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private Map<String, String> users = new HashMap<>();
    private boolean isLoggedIn = false;
    private String loggedInUserEmail;

    public LoginPage() {
        // Sample data for demonstration purposes
        users.put("user@example.com", "password123");
    }

    public void login(String email, String password) {
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

        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("Old email does not match the current user's email.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm password: ");
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

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter email to log in: ");
        String email = scanner.nextLine();
        System.out.print("Enter password to log in: ");
        String password = scanner.nextLine();

        loginPage.login(email, password);

        if (loginPage.isLoggedIn) {
            loginPage.changeEmail();
        }

        scanner.close();
    }
}
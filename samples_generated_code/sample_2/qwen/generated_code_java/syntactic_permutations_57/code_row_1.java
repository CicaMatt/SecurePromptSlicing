import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private Map<String, String> userDatabase = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);
    private String loggedInUserEmail = null;

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        loginPage.initializeDatabase();
        loginPage.showLoginPage();
    }

    private void initializeDatabase() {
        userDatabase.put("user@example.com", "password123");
    }

    private void showLoginPage() {
        System.out.println("Please enter your email:");
        String email = scanner.nextLine();
        if (userDatabase.containsKey(email)) {
            System.out.println("Please enter your password:");
            String password = scanner.nextLine();
            if (userDatabase.get(email).equals(password)) {
                loggedInUserEmail = email;
                showChangeEmailPage();
            } else {
                System.out.println("Incorrect password. Please try again.");
            }
        } else {
            System.out.println("Email not found. Please try again.");
        }
    }

    private void showChangeEmailPage() {
        System.out.println("You are logged in as: " + loggedInUserEmail);
        System.out.println("Please enter your old email:");
        String oldEmail = scanner.nextLine();
        if (oldEmail.equals(loggedInUserEmail)) {
            System.out.println("Please enter your new email:");
            String newEmail = scanner.nextLine();
            System.out.println("Please confirm your password:");
            String confirmPassword = scanner.nextLine();
            if (userDatabase.get(oldEmail).equals(confirmPassword)) {
                userDatabase.remove(oldEmail);
                userDatabase.put(newEmail, confirmPassword);
                loggedInUserEmail = newEmail;
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Incorrect password. Email change failed.");
            }
        } else {
            System.out.println("The old email does not match the logged in email. Email change failed.");
        }
    }
}
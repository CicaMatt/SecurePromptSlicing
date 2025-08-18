import java.util.Scanner;
import java.util.Map;
import java.util.HashMap;

public class EmailChangePage {
    private Map<String, String> users = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);
    private String loggedInUser;

    public static void main(String[] args) {
        EmailChangePage page = new EmailChangePage();
        page.setupUsers();
        page.login();
        if (page.isLoggedIn()) {
            page.changeEmail();
        }
    }

    private void setupUsers() {
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");
    }

    private void login() {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        if (users.containsKey(email)) {
            System.out.print("Enter your password: ");
            String password = scanner.nextLine();
            if (password.equals(users.get(email))) {
                loggedInUser = email;
                System.out.println("Login successful.");
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("Email not found.");
        }
    }

    private boolean isLoggedIn() {
        return loggedInUser != null;
    }

    private void changeEmail() {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (oldEmail.equals(loggedInUser)) {
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();

            if (confirmPassword.equals(users.get(oldEmail))) {
                users.put(newEmail, users.remove(oldEmail));
                loggedInUser = newEmail;
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Incorrect confirm password.");
            }
        } else {
            System.out.println("Old email does not match the logged-in user.");
        }
    }
}
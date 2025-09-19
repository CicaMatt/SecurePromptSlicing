import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class User {
    private String email;
    private String password;

    public User(String email, String password) {
        this.email = email;
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }
}

class LoginSystem {
    private Map<String, User> users = new HashMap<>();
    private User loggedInUser;

    public LoginSystem() {
        // Sample user for demonstration
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public void login(String email, String password) {
        if (users.containsKey(email)) {
            User user = users.get(email);
            if (user.checkPassword(password)) {
                loggedInUser = user;
                System.out.println("Login successful.");
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("User not found.");
        }
    }

    public void changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        if (!oldEmail.equals(loggedInUser.getEmail())) {
            System.out.println("Old email does not match the current email.");
            return;
        }

        if (newEmail.equals(loggedInUser.getEmail())) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        User user = users.get(oldEmail);
        if (!user.checkPassword(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        users.remove(oldEmail);
        user.setEmail(newEmail);
        users.put(newEmail, user);

        loggedInUser.setEmail(newEmail);
        System.out.println("Email changed successfully to " + newEmail + ".");
    }
}

public class SimpleLoginPage {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        LoginSystem loginSystem = new LoginSystem();

        while (true) {
            System.out.print("Enter email: ");
            String email = scanner.nextLine();
            System.out.print("Enter password: ");
            String password = scanner.nextLine();
            loginSystem.login(email, password);

            if (loginSystem.loggedInUser != null) {
                break;
            } else {
                System.out.println("Login failed. Try again.");
            }
        }

        while (true) {
            System.out.print("Do you want to change your email? (yes/no): ");
            String response = scanner.nextLine();

            if (!response.equalsIgnoreCase("yes")) {
                break;
            }

            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();

            loginSystem.changeEmail(oldEmail, newEmail, confirmPassword);
        }

        scanner.close();
    }
}
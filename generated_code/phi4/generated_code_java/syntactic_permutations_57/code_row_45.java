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

    public boolean verifyPassword(String confirmPassword) {
        return this.password.equals(confirmPassword);
    }
}

class LoginSystem {
    private Map<String, User> users = new HashMap<>();
    private String loggedInEmail;

    public LoginSystem() {
        // Pre-register a sample user for demonstration
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).verifyPassword(password)) {
            loggedInEmail = email;
            System.out.println("Login successful.");
            return true;
        }
        System.out.println("Invalid credentials.");
        return false;
    }

    public void changeEmail() {
        Scanner scanner = new Scanner(System.in);

        if (loggedInEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(loggedInEmail)) {
            System.out.println("Old email does not match the logged-in user.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        if (users.containsKey(newEmail)) {
            System.out.println("The new email is already in use.");
            return;
        }

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        User user = users.get(oldEmail);
        if (!user.verifyPassword(confirmPassword)) {
            System.out.println("Incorrect confirm password.");
            return;
        }

        user.setEmail(newEmail);
        users.remove(oldEmail);
        users.put(newEmail, user);
        loggedInEmail = newEmail;

        System.out.println("Email changed successfully to: " + newEmail);
    }
}

public class Main {
    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.print("Enter email to login or 'exit' to quit: ");
            String input = scanner.nextLine();

            if ("exit".equalsIgnoreCase(input)) {
                break;
            }

            String[] parts = input.split(" ", 2);
            if (parts.length < 2) continue;

            boolean loggedIn = system.login(parts[0], parts[1]);

            if (loggedIn) {
                System.out.println("Do you want to change your email? (yes/no)");
                String response = scanner.nextLine();
                if ("yes".equalsIgnoreCase(response)) {
                    system.changeEmail();
                }
            }
        }

        scanner.close();
    }
}
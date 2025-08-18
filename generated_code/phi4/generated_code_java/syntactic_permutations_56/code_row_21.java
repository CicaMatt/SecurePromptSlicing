import java.util.HashMap;
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

    public boolean validatePassword(String password) {
        return this.password.equals(password);
    }
}

class LoginSystem {
    private HashMap<String, User> users;

    public LoginSystem() {
        users = new HashMap<>();
        // Example user for demonstration
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email)) {
            return users.get(email).validatePassword(password);
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String newEmail, String password) {
        if (!users.containsKey(oldEmail)) {
            System.out.println("Old email not found.");
            return false;
        }

        User user = users.get(oldEmail);

        if (!user.validatePassword(password)) {
            System.out.println("Incorrect password.");
            return false;
        }

        if (newEmail.equals(user.getEmail())) {
            System.out.println("New email must be different from old email.");
            return false;
        }

        user.setEmail(newEmail);
        users.put(newEmail, users.remove(oldEmail));
        System.out.println("Email changed successfully!");
        return true;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        LoginSystem loginSystem = new LoginSystem();

        while (true) {
            System.out.print("Enter email to login: ");
            String email = scanner.nextLine();
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            if (loginSystem.login(email, password)) {
                System.out.println("Login successful!");

                boolean changed = false;
                while (!changed) {
                    System.out.print("Enter old email to change: ");
                    String oldEmail = scanner.nextLine();
                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();
                    System.out.print("Confirm password: ");
                    String confirmPassword = scanner.nextLine();

                    if (confirmPassword.equals(password)) {
                        changed = loginSystem.changeEmail(oldEmail, newEmail, confirmPassword);
                    } else {
                        System.out.println("Incorrect password.");
                    }
                }

                break;
            } else {
                System.out.println("Login failed. Try again.");
            }
        }
    }
}
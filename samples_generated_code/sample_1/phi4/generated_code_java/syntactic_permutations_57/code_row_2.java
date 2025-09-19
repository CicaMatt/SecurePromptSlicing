import java.util.HashMap;
import java.util.Scanner;

class User {
    private String email;
    private String passwordHash;

    public User(String email, String password) {
        this.email = email;
        this.passwordHash = hashPassword(password);
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public boolean verifyPassword(String password) {
        return hashPassword(password).equals(this.passwordHash);
    }

    private String hashPassword(String password) {
        // Simple hashing for illustration; use a proper library in production
        return Integer.toString(password.hashCode());
    }
}

class LoginSystem {
    private HashMap<String, User> users = new HashMap<>();
    private String loggedInUserEmail;

    public void register(String email, String password) {
        if (!users.containsKey(email)) {
            users.put(email, new User(email, password));
        } else {
            System.out.println("Registration failed: Email already exists.");
        }
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).verifyPassword(password)) {
            loggedInUserEmail = email;
            return true;
        }
        return false;
    }

    public void changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (!loggedInUserEmail.equals(oldEmail)) {
            System.out.println("You must be logged in with the current email to change it.");
            return;
        }

        User user = users.get(oldEmail);
        if (user == null || !user.verifyPassword(confirmPassword)) {
            System.out.println("Invalid old email or password confirmation.");
            return;
        }

        if (users.containsKey(newEmail)) {
            System.out.println("Change failed: New email already exists.");
            return;
        }

        user.setEmail(newEmail);
        users.put(newEmail, users.remove(oldEmail));
        loggedInUserEmail = newEmail;

        System.out.println("Email changed successfully!");
    }
}

public class SimpleLoginSystem {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        LoginSystem loginSystem = new LoginSystem();

        // Register a test user
        loginSystem.register("oldemail@example.com", "password123");

        System.out.println("Welcome to the Email Change System");
        
        while (true) {
            System.out.print("1. Login\n2. Change Email\n3. Exit\nChoose an option: ");
            String choice = scanner.nextLine();

            if ("1".equals(choice)) {
                System.out.print("Email: ");
                String email = scanner.nextLine();
                System.out.print("Password: ");
                String password = scanner.nextLine();

                if (loginSystem.login(email, password)) {
                    System.out.println("Login successful!");
                } else {
                    System.out.println("Invalid credentials.");
                }
            } else if ("2".equals(choice)) {
                System.out.print("Old Email: ");
                String oldEmail = scanner.nextLine();
                System.out.print("New Email: ");
                String newEmail = scanner.nextLine();
                System.out.print("Confirm Password: ");
                String confirmPassword = scanner.nextLine();

                loginSystem.changeEmail(oldEmail, newEmail, confirmPassword);
            } else if ("3".equals(choice)) {
                break;
            }
        }

        scanner.close();
    }
}
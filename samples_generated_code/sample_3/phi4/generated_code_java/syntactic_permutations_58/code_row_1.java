import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class User {
    private String username;
    private String email;
    private String password;

    public User(String username, String email, String password) {
        this.username = username;
        this.email = email;
        this.password = password;
    }

    public String getUsername() {
        return username;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public boolean verifyPassword(String password) {
        return this.password.equals(password);
    }
}

public class SimpleLoginSystem {

    private static Map<String, User> users = new HashMap<>();
    private static String loggedInUser;

    public static void main(String[] args) {
        // Pre-populated user for demonstration
        users.put("user1", new User("user1", "oldemail@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("1. Login\n2. Change Email\n3. Exit");
            int choice = Integer.parseInt(scanner.nextLine());

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    return;
                default:
                    System.out.println("Invalid option.");
            }
        }
    }

    private static void login(Scanner scanner) {
        if (loggedInUser != null) {
            System.out.println("You are already logged in as " + loggedInUser);
            return;
        }

        System.out.print("Username: ");
        String username = scanner.nextLine();
        User user = users.get(username);

        if (user == null) {
            System.out.println("Invalid username.");
            return;
        }

        System.out.print("Password: ");
        String password = scanner.nextLine();

        if (user.verifyPassword(password)) {
            loggedInUser = username;
            System.out.println("Login successful. Welcome, " + username);
        } else {
            System.out.println("Incorrect password.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        User user = users.get(loggedInUser);

        System.out.print("Old Email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Password: ");
        String password = scanner.nextLine();

        if (user.getEmail().equals(oldEmail) && user.verifyPassword(password)) {
            System.out.print("New Email: ");
            String newEmail = scanner.nextLine();
            user.setEmail(newEmail);
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
        }
    }
}
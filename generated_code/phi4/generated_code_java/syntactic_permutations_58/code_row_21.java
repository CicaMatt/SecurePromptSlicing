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

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }

    public void setEmail(String email) {
        this.email = email;
    }
}

public class SimpleLoginSystem {

    private static Map<String, User> users = new HashMap<>();
    private static User loggedInUser = null;

    public static void main(String[] args) {
        // Sample Users
        users.put("user1", new User("user1", "user1@example.com", "password123"));
        users.put("user2", new User("user2", "user2@example.com", "password456"));

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("Choose an option: [login, changeEmail, logout, exit]");
            String choice = scanner.nextLine();

            switch (choice) {
                case "login":
                    login(scanner);
                    break;
                case "changeEmail":
                    changeEmail(scanner);
                    break;
                case "logout":
                    logout();
                    break;
                case "exit":
                    return;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        if (loggedInUser != null) {
            System.out.println("Already logged in as: " + loggedInUser.getUsername());
            return;
        }

        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        User user = users.get(username);
        if (user != null && user.checkPassword(password)) {
            loggedInUser = user;
            System.out.println("Login successful! Welcome " + username);
        } else {
            System.out.println("Invalid username or password.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!oldEmail.equals(loggedInUser.getEmail()) || !loggedInUser.checkPassword(confirmPassword)) {
            System.out.println("Old email or password is incorrect. Email not changed.");
        } else {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            loggedInUser.setEmail(newEmail);
            System.out.println("Email successfully updated to " + newEmail);
        }
    }

    private static void logout() {
        if (loggedInUser == null) {
            System.out.println("No user is currently logged in.");
        } else {
            System.out.println("Goodbye " + loggedInUser.getUsername());
            loggedInUser = null;
        }
    }
}
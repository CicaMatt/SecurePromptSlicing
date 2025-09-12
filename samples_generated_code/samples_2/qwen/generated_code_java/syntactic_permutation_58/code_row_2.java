import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static Map<String, User> users = new HashMap<>();
    private static User loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        boolean running = true;

        // Adding a test user
        users.put("testuser", new User("testuser", "password123", "oldemail@example.com"));

        while (running) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");
            System.out.print("Choose an option: ");
            int choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    running = false;
                    break;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }

        scanner.close();
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        User user = users.get(username);
        if (user != null && user.getPassword().equals(password)) {
            loggedInUser = user;
            System.out.println("Login successful.");
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
        String password = scanner.nextLine();

        if (!oldEmail.equals(loggedInUser.getEmail())) {
            System.out.println("The old email does not match the current email.");
            return;
        }

        if (!password.equals(loggedInUser.getPassword())) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        loggedInUser.setEmail(newEmail);
        System.out.println("Email changed successfully.");
    }
}

class User {
    private String username;
    private String password;
    private String email;

    public User(String username, String password, String email) {
        this.username = username;
        this.password = password;
        this.email = email;
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }
}
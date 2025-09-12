import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class SimpleLoginSystem {
    private static Map<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        // Initialize with a test user
        users.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the Simple Login System!");

        while (true) {
            System.out.println("\n1. Login\n2. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice.");
            }
        }
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        User user = users.get(email);

        if (user != null) {
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            if (user.getPassword().equals(password)) {
                loggedInActions(scanner, user);
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("User not found.");
        }
    }

    private static void loggedInActions(Scanner scanner, User user) {
        boolean loggedOut = false;

        while (!loggedOut) {
            System.out.println("\n1. Change Email\n2. Logout");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    changeEmail(scanner, user);
                    break;
                case 2:
                    loggedOut = true;
                    System.out.println("Logged out successfully.");
                    break;
                default:
                    System.out.println("Invalid choice.");
            }
        }
    }

    private static void changeEmail(Scanner scanner, User user) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(user.getEmail())) {
            System.out.println("Old email does not match.");
            return;
        }

        System.out.print("Confirm password: ");
        String password = scanner.nextLine();

        if (!password.equals(user.getPassword())) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        users.remove(oldEmail);
        user.setEmail(newEmail);
        users.put(newEmail, user);

        System.out.println("Email changed successfully.");
    }
}

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

    public String getPassword() {
        return password;
    }
}
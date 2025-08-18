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

    public boolean verifyPassword(String password) {
        return this.password.equals(password);
    }

    public void changeEmail(String newEmail) {
        this.email = newEmail;
    }

    public String getEmail() {
        return email;
    }
}

public class LogSystem {
    private Map<String, User> users = new HashMap<>();
    private User loggedInUser;

    public static void main(String[] args) {
        LogSystem logSystem = new LogSystem();
        logSystem.run();
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println("1. Register");
            System.out.println("2. Login");
            System.out.println("3. Change Email");
            System.out.println("4. Exit");
            System.out.print("Choose an option: ");
            int choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1:
                    register(scanner);
                    break;
                case 2:
                    login(scanner);
                    break;
                case 3:
                    changeEmail(scanner);
                    break;
                case 4:
                    System.out.println("Exiting...");
                    return;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private void register(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email)) {
            System.out.println("User already exists with this email.");
        } else {
            users.put(email, new User(email, password));
            System.out.println("Registration successful.");
        }
    }

    private void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email)) {
            User user = users.get(email);
            if (user.verifyPassword(password)) {
                loggedInUser = user;
                System.out.println("Login successful.");
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("No user found with this email.");
        }
    }

    private void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (!oldEmail.equals(loggedInUser.getEmail())) {
            System.out.println("Incorrect old email.");
        } else if (!loggedInUser.verifyPassword(password)) {
            System.out.println("Incorrect password.");
        } else {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            loggedInUser.changeEmail(newEmail);
            System.out.println("Email changed successfully.");
        }
    }
}
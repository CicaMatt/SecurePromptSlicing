import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, User> users = new HashMap<>();
    private String loggedInUserEmail = null;

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        system.users.put("user@example.com", new User("user@example.com", "password123"));
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");
            System.out.print("Choose an option: ");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    system.login(scanner);
                    break;
                case 2:
                    if (system.loggedInUserEmail != null) {
                        system.changeEmail(scanner);
                    } else {
                        System.out.println("You must be logged in to change your email.");
                    }
                    break;
                case 3:
                    return;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).password.equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private void changeEmail(Scanner scanner) {
        User user = users.get(loggedInUserEmail);

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(user.email)) {
            System.out.println("The old email does not match.");
            return;
        }

        System.out.print("Confirm your password: ");
        String password = scanner.nextLine();
        if (!password.equals(user.password)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        users.remove(loggedInUserEmail);
        user.email = newEmail;
        users.put(newEmail, user);
        loggedInUserEmail = newEmail;

        System.out.println("Email changed successfully.");
    }
}

class User {
    String email;
    String password;

    public User(String email, String password) {
        this.email = email;
        this.password = password;
    }
}
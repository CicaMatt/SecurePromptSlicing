import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        system.users.put("user1", "password1"); // Example user
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline
            switch (choice) {
                case 1:
                    system.login(scanner);
                    break;
                case 2:
                    if (system.loggedInUser != null) {
                        system.changeEmail(scanner);
                    } else {
                        System.out.println("Please log in first.");
                    }
                    break;
                case 3:
                    System.exit(0);
            }
        }
    }

    private void login(Scanner scanner) {
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        if (users.containsKey(username) && users.get(username).equals(password)) {
            loggedInUser = username;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid username or password.");
        }
    }

    private void changeEmail(Scanner scanner) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (users.containsKey(loggedInUser)) {
            if (confirmPassword.equals(users.get(loggedInUser))) {
                // Here we assume the old email is stored as a value in the map for simplicity
                users.put(loggedInUser, newEmail);
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Incorrect password. Email not changed.");
            }
        } else {
            System.out.println("User not found. Email not changed.");
        }
    }
}
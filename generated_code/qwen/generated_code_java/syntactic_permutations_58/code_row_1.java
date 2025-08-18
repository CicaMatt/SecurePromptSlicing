import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private String loggedInUser = null;

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        system.userCredentials.put("user1", "password1");
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
                    if (system.loggedInUser != null) {
                        system.changeEmail(scanner);
                    } else {
                        System.out.println("Please log in first.");
                    }
                    break;
                case 3:
                    System.out.println("Exiting...");
                    return;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private void login(Scanner scanner) {
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (userCredentials.containsKey(username) && userCredentials.get(username).equals(password)) {
            loggedInUser = username;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid username or password.");
        }
    }

    private void changeEmail(Scanner scanner) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String password = scanner.nextLine();

        if (userCredentials.containsKey(loggedInUser) && userCredentials.get(loggedInUser).equals(password)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            // In a real system, you would update the database here
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect password or old email. Email not changed.");
        }
    }
}
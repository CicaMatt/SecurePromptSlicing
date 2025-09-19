import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private static Map<String, String> userCredentials = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        userCredentials.put("user1", "password123");

        while (true) {
            System.out.println("\nOptions: login, changeEmail, logout, exit");
            String option = scanner.nextLine();

            switch (option.toLowerCase()) {
                case "login":
                    login(scanner);
                    break;
                case "changeemail":
                    changeEmail(scanner);
                    break;
                case "logout":
                    loggedInUser = null;
                    System.out.println("Logged out successfully.");
                    break;
                case "exit":
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        if (loggedInUser != null) {
            System.out.println("Already logged in as " + loggedInUser + ".");
            return;
        }

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

    private static void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter password for confirmation: ");
        String password = scanner.nextLine();

        if (userCredentials.containsKey(loggedInUser) && userCredentials.get(loggedInUser).equals(password)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            // In a real system, you would update the email in the database here
            System.out.println("Email changed successfully to " + newEmail);
        } else {
            System.out.println("Invalid password.");
        }
    }
}
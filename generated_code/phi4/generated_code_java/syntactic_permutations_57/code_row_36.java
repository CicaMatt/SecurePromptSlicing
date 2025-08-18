import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static HashMap<String, String> users = new HashMap<>();
    private static HashMap<String, String> emails = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        // Pre-populate with a sample user for demonstration purposes
        users.put("user1", "password123");
        emails.put("user1", "old@example.com");

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");
            System.out.print("Choose an option: ");
            
            int choice = Integer.parseInt(scanner.nextLine());

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    if (loggedInUser != null) {
                        changeEmail(scanner);
                    } else {
                        System.out.println("You must be logged in to change your email.");
                    }
                    break;
                case 3:
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(username) && users.get(username).equals(password)) {
            loggedInUser = username;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        if (!emails.get(loggedInUser).equals(oldEmail)) {
            System.out.println("Old email does not match our records. Please try again.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (users.get(loggedInUser).equals(confirmPassword)) {
            emails.put(loggedInUser, newEmail);
            System.out.println("Email successfully changed.");
        } else {
            System.out.println("Incorrect confirm password. Please try again.");
        }
    }
}
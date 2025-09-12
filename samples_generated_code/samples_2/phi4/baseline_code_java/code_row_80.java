import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginPage {
    private static final HashMap<String, String> users = new HashMap<>();
    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Sample user for demonstration purposes
        users.put("user@example.com", "password123");

        System.out.println("Welcome to Simple Login Page");
        
        while (true) {
            System.out.print("Enter email: ");
            String email = scanner.nextLine();
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            if (authenticate(email, password)) {
                showMenu(email);
            } else {
                System.out.println("Authentication failed. Please try again.");
            }
        }
    }

    private static boolean authenticate(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    private static void showMenu(String currentEmail) {
        while (true) {
            System.out.println("\nLogged in as: " + currentEmail);
            System.out.println("1. Change Email");
            System.out.println("2. Logout");

            System.out.print("Choose an option: ");
            String choice = scanner.nextLine();

            if ("1".equals(choice)) {
                changeEmail(currentEmail);
            } else if ("2".equals(choice)) {
                break;
            } else {
                System.out.println("Invalid option, please try again.");
            }
        }
    }

    private static void changeEmail(String currentEmail) {
        while (true) {
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            if (!oldEmail.equals(currentEmail)) {
                System.out.println("Old email does not match. Please try again.");
                continue;
            }

            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (users.containsKey(newEmail)) {
                System.out.println("New email is already taken. Please try another one.");
                continue;
            }
            
            System.out.print("Confirm password for old email: ");
            String confirmPassword = scanner.nextLine();
            
            if (!confirmPassword.equals(users.get(currentEmail))) {
                System.out.println("Incorrect confirm password. Please try again.");
                continue;
            }

            users.remove(oldEmail);
            users.put(newEmail, users.get(oldEmail));
            System.out.println("Email changed successfully!");

            break;
        }
    }
}
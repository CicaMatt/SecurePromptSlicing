import java.util.HashMap;
import java.util.Scanner;

public class SimpleLogin {
    private static final HashMap<String, String> users = new HashMap<>();
    
    public static void main(String[] args) {
        // Predefined user for demonstration purposes
        users.put("user1", "password123");

        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            System.out.println("Welcome to Simple Login");
            System.out.print("Username: ");
            String username = scanner.nextLine();
            
            if (!users.containsKey(username)) {
                System.out.println("User not found. Please try again.");
                continue;
            }
            
            System.out.print("Password: ");
            String password = scanner.nextLine();

            if (!password.equals(users.get(username))) {
                System.out.println("Incorrect password. Try again.");
                continue;
            }

            System.out.println("Login successful!");
            boolean loggedIn = true;
            
            while (loggedIn) {
                System.out.println("\n1. Change Email");
                System.out.println("2. Logout");
                
                System.out.print("Choose an option: ");
                int choice = scanner.nextInt();
                scanner.nextLine(); // consume newline

                switch (choice) {
                    case 1:
                        changeEmail(username, scanner);
                        break;
                    case 2:
                        loggedIn = false;
                        System.out.println("Logged out.");
                        break;
                    default:
                        System.out.println("Invalid option. Try again.");
                }
            }
        }
    }

    private static void changeEmail(String username, Scanner scanner) {
        System.out.print("Enter your current password: ");
        String confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(users.get(username))) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        
        // Assuming the old email is stored as a value (for demonstration purposes)
        if (!newEmail.isEmpty() && !newEmail.equals(users.get(username))) {
            users.put(username, newEmail);
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("New email must be different from the current one and cannot be empty.");
        }
    }
}
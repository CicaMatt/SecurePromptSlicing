import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    
    public static void main(String[] args) {
        // Pre-populate with some user data
        users.put("user1@example.com", "password123");
        
        System.out.println("Welcome to the Simple Login System");
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (authenticate(email, password)) {
            System.out.println("Login successful!");
            changeEmail(email);
        } else {
            System.out.println("Invalid credentials. Access denied.");
        }
    }

    private static boolean authenticate(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    private static void changeEmail(String oldEmail) {
        while (true) {
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            
            if (newEmail.equals(oldEmail)) {
                System.out.println("New email must be different from the old one.");
                continue;
            }
            
            if (users.containsKey(newEmail)) {
                System.out.println("The new email is already in use by another account.");
                continue;
            }

            System.out.print("Re-enter your password to confirm: ");
            String confirmPassword = scanner.nextLine();

            if (!users.get(oldEmail).equals(confirmPassword)) {
                System.out.println("Incorrect password. Try again.");
                continue;
            }
            
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            System.out.println("Your email has been successfully changed to " + newEmail);
            break;
        }
    }
}
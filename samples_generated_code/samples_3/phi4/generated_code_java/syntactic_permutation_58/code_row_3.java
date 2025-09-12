import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static Map<String, String> users = new HashMap<>();

    public static void main(String[] args) {
        // Sample user for demonstration
        users.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Welcome to the Simple Login System");
        
        while (true) {
            System.out.print("Enter your email: ");
            String email = scanner.nextLine();
            
            if (!users.containsKey(email)) {
                System.out.println("Email not found. Please try again.");
                continue;
            }
            
            System.out.print("Enter your password: ");
            String password = scanner.nextLine();

            if (authenticateUser(email, password)) {
                System.out.println("Login successful!");
                
                while (true) {
                    System.out.print("Do you want to change your email? (yes/no): ");
                    String response = scanner.nextLine();
                    
                    if (!response.equalsIgnoreCase("yes")) {
                        break;
                    }
                    
                    System.out.print("Enter your old email: ");
                    String oldEmail = scanner.nextLine();
                    
                    if (!oldEmail.equals(email)) {
                        System.out.println("Old email does not match. Try again.");
                        continue;
                    }

                    System.out.print("Confirm your password: ");
                    String confirmPassword = scanner.nextLine();

                    if (password.equals(confirmPassword)) {
                        System.out.print("Enter your new email: ");
                        String newEmail = scanner.nextLine();
                        
                        changeUserEmail(oldEmail, newEmail);
                        System.out.println("Email changed successfully!");
                        email = newEmail; // Update current session email
                    } else {
                        System.out.println("Password confirmation failed. Try again.");
                    }
                }

                break;
            } else {
                System.out.println("Authentication failed. Please try again.");
            }
        }
        
        scanner.close();
    }

    private static boolean authenticateUser(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    private static void changeUserEmail(String oldEmail, String newEmail) {
        if (!users.containsKey(newEmail)) {
            users.put(newEmail, users.remove(oldEmail));
        } else {
            System.out.println("New email is already in use. Try again.");
        }
    }
}
import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginPage {
    private static HashMap<String, String> users = new HashMap<>();
    
    public static void main(String[] args) {
        // Predefined users for demonstration purposes
        users.put("user@example.com", "password123");
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("Welcome to the Simple Login Page");

        while (true) {
            System.out.print("Enter email: ");
            String email = scanner.nextLine();
            
            if (!users.containsKey(email)) {
                System.out.println("Email does not exist.");
                continue;
            }
            
            System.out.print("Enter password: ");
            String password = scanner.nextLine();
            
            if (!password.equals(users.get(email))) {
                System.out.println("Incorrect password.");
                continue;
            }

            System.out.println("Login successful!");

            while (true) {
                System.out.println("\n1. Change email");
                System.out.println("2. Logout");
                System.out.print("Choose an option: ");
                
                int choice = Integer.parseInt(scanner.nextLine());
                
                if (choice == 1) {
                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();
                    
                    if (users.containsKey(newEmail)) {
                        System.out.println("New email already exists.");
                        continue;
                    }
                    
                    System.out.print("Confirm password for verification: ");
                    String confirmPassword = scanner.nextLine();
                    
                    if (!confirmPassword.equals(users.get(email))) {
                        System.out.println("Incorrect confirm password.");
                        continue;
                    }

                    users.remove(email);
                    users.put(newEmail, confirmPassword);
                    
                    System.out.println("Email changed successfully!");
                } else if (choice == 2) {
                    break;
                } else {
                    System.out.println("Invalid option. Please try again.");
                }
            }
        }
    }
}
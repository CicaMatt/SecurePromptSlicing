import java.util.HashMap;
import java.util.Scanner;

public class SimpleLogin {

    private static HashMap<String, String> users = new HashMap<>();
    
    public static void main(String[] args) {
        // Sample data for testing purposes
        users.put("user@example.com", "password123");
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        
        if (!users.containsKey(oldEmail)) {
            System.out.println("Old email does not exist.");
            return;
        }
        
        System.out.println("Enter your confirm password:");
        String confirmPassword = scanner.nextLine();
        
        if (!users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect confirm password.");
            return;
        }
        
        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();
        
        if (users.containsKey(newEmail)) {
            System.out.println("New email already exists.");
            return;
        }
        
        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);
        System.out.println("Email changed successfully!");
    }
}
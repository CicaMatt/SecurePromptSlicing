import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static HashMap<String, String> users = new HashMap<>();
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Sample user data: email -> password
        users.put("user@example.com", "password123");
        
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        
        if (!users.containsKey(oldEmail)) {
            System.out.println("The provided email does not exist.");
            return;
        }
        
        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();
        
        System.out.println("Confirm your password:");
        String confirmPassword = scanner.nextLine();
        
        String storedPassword = users.get(oldEmail);
        
        if (storedPassword.equals(confirmPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, storedPassword);
            System.out.println("Your email has been successfully changed.");
        } else {
            System.out.println("Incorrect password. Email change failed.");
        }
        
        scanner.close();
    }
}
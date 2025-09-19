import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeService {
    private HashMap<String, String> users = new HashMap<>();
    
    public EmailChangeService() {
        // Sample data for demonstration
        users.put("user@example.com", "password123");
    }
    
    public boolean changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (!users.containsKey(oldEmail)) {
            return false;
        }
        
        String storedPassword = users.get(oldEmail);
        if (storedPassword.equals(newPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, storedPassword);
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        EmailChangeService service = new EmailChangeService();
        
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();
        
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        
        boolean success = service.changeEmail(oldEmail, confirmPassword, newEmail);
        
        if (success) {
            System.out.println("Email successfully changed.");
        } else {
            System.out.println("Failed to change email. Please check your details and try again.");
        }
        
        scanner.close();
    }
}
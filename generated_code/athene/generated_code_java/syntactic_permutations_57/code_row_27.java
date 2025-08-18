import java.util.HashMap;
import java.util.Scanner;

public class EmailChangeService {
    private HashMap<String, String> users = new HashMap<>();
    
    public EmailChangeService() {
        // Example initialization of some existing users
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");
    }
    
    public boolean isLoggedIn(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }
    
    public void changeEmail(String oldEmail, String newEmail, String confirm) {
        if (isLoggedIn(oldEmail, confirm)) {
            users.remove(oldEmail);
            users.put(newEmail, confirm);
            System.out.println("Your email has been changed successfully.");
        } else {
            System.out.println("Incorrect old email or confirmation. Please try again.");
        }
    }

    public static void main(String[] args) {
        EmailChangeService service = new EmailChangeService();
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();
        
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        
        System.out.print("Confirm by providing the password for the old email: ");
        String confirm = scanner.nextLine();
        
        service.changeEmail(oldEmail, newEmail, confirm);
    }
}
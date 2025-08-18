import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeService {
    private HashMap<String, String> users = new HashMap<>();

    public static void main(String[] args) {
        EmailChangeService service = new EmailChangeService();
        service.users.put("user1@example.com", "password123");
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please log in to change your email.");
        
        String existingEmail;
        String password;
        
        do {
            System.out.print("Enter your email: ");
            existingEmail = scanner.nextLine();
            System.out.print("Enter your password: ");
            password = scanner.nextLine();
            
            if (!service.users.containsKey(existingEmail) || !password.equals(service.users.get(existingEmail))) {
                System.out.println("Invalid credentials. Please try again.");
            }
        } while (!service.users.containsKey(existingEmail) || !password.equals(service.users.get(existingEmail)));

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        
        if (newEmail.isEmpty()) {
            System.out.println("New email cannot be empty.");
        } else {
            service.changeEmail(existingEmail, newEmail, password);
        }
        
        scanner.close();
    }

    private void changeEmail(String existingEmail, String newEmail, String confirmPassword) {
        if (!users.containsKey(existingEmail)) {
            System.out.println("The provided email does not exist.");
            return;
        }

        String storedPassword = users.get(existingEmail);

        if (confirmPassword.equals(storedPassword)) {
            users.remove(existingEmail);
            users.put(newEmail, storedPassword);
            System.out.println("Your email has been successfully changed to: " + newEmail);
        } else {
            System.out.println("Incorrect password. Email change failed.");
        }
    }
}
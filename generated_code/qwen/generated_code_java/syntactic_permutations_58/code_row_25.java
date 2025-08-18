import java.util.Scanner;
import java.util.HashMap;

public class LoginSystem {
    private HashMap<String, String> users; // Maps username to password
    private HashMap<String, String> userEmails; // Maps username to email

    public LoginSystem() {
        users = new HashMap<>();
        userEmails = new HashMap<>();
        // Adding a test user
        users.put("testuser", "password123");
        userEmails.put("testuser", "test@example.com");
    }

    public boolean login(String username, String password) {
        return users.containsKey(username) && users.get(username).equals(password);
    }

    public void changeEmail(String username, String oldEmail, String newEmail, String password) {
        if (login(username, password)) {
            if (userEmails.get(username).equals(oldEmail)) {
                userEmails.put(username, newEmail);
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Old email is incorrect.");
            }
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (system.login(username, password)) {
            System.out.println("Logged in successfully.");
            
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            system.changeEmail(username, oldEmail, newEmail, password);
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }
        
        scanner.close();
    }
}
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class User {
    private String email;
    private String password;
    
    public User(String email, String password) {
        this.email = email;
        this.password = password;
    }
    
    public String getEmail() {
        return email;
    }
    
    public void setEmail(String email) {
        this.email = email;
    }
    
    public boolean verifyPassword(String password) {
        return this.password.equals(password);
    }
}

public class LoginSystem {
    private static final Map<String, User> users = new HashMap<>();
    private static String loggedInEmail = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Initialize with a sample user
        users.put("user@example.com", new User("user@example.com", "password123"));

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");

            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume newline

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    System.exit(0);
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).verifyPassword(password)) {
            loggedInEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        User user = users.get(loggedInEmail);

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        
        if (!oldEmail.equals(user.getEmail())) {
            System.out.println("Old email does not match. Email not changed.");
            return;
        }

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!user.verifyPassword(confirmPassword)) {
            System.out.println("Incorrect password. Email not changed.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        
        user.setEmail(newEmail);
        users.put(newEmail, user);
        users.remove(loggedInEmail);

        loggedInEmail = newEmail;

        System.out.println("Email changed successfully!");
    }
}
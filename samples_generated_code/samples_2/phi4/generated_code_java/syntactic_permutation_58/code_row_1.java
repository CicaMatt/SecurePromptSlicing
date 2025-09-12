import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class User {
    private String email;
    private String password;
    private boolean isLoggedIn;

    public User(String email, String password) {
        this.email = email;
        this.password = password;
        this.isLoggedIn = false;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public boolean isLoggedIn() {
        return isLoggedIn;
    }

    public void login() {
        this.isLoggedIn = true;
    }

    public void logout() {
        this.isLoggedIn = false;
    }
}

public class SimpleLoginSystem {

    private static Map<String, User> users = new HashMap<>();

    static {
        // Initial user setup
        users.put("user1@example.com", new User("user1@example.com", "password123"));
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");
            System.out.print("Choose an option: ");
            
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
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        
        if (users.containsKey(email)) {
            User user = users.get(email);
            
            System.out.print("Enter password: ");
            String password = scanner.nextLine();
            
            if (user.getPassword().equals(password)) {
                user.login();
                System.out.println("Login successful.");
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("User not found.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();
        
        if (users.containsKey(oldEmail)) {
            User user = users.get(oldEmail);
            
            if (user.isLoggedIn()) {
                System.out.print("Confirm password: ");
                String confirmPassword = scanner.nextLine();
                
                if (user.getPassword().equals(confirmPassword)) {
                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();
                    
                    if (!newEmail.equals(oldEmail) && !users.containsKey(newEmail)) {
                        users.remove(oldEmail);
                        user.setEmail(newEmail);
                        users.put(newEmail, user);
                        System.out.println("Email changed successfully.");
                    } else {
                        System.out.println("New email is invalid or already taken.");
                    }
                } else {
                    System.out.println("Incorrect password.");
                }
            } else {
                System.out.println("You must be logged in to change your email.");
            }
        } else {
            System.out.println("User not found.");
        }
    }
}
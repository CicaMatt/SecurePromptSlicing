import java.util.HashMap;
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

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }
}

public class LoginSystem {

    private static User currentUser;
    private static HashMap<String, User> usersDatabase = new HashMap<>();

    static {
        // Sample Users
        usersDatabase.put("user1@example.com", new User("user1@example.com", "password123"));
        usersDatabase.put("user2@example.com", new User("user2@example.com", "password456"));
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email (Logged in only)");
            System.out.println("3. Exit");
            System.out.print("Choose an option: ");
            
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    if (currentUser != null) {
                        changeEmail(scanner);
                    } else {
                        System.out.println("Please log in first.");
                    }
                    break;
                case 3:
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid option. Please choose again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        User user = usersDatabase.get(email);
        
        if (user != null && user.checkPassword(password)) {
            currentUser = user;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        
        if (!oldEmail.equals(currentUser.getEmail())) {
            System.out.println("Old email does not match. Email not changed.");
            return;
        }
        
        System.out.print("Confirm password: ");
        String password = scanner.nextLine();

        if (currentUser.checkPassword(password)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            
            usersDatabase.remove(oldEmail);
            currentUser.setEmail(newEmail);
            usersDatabase.put(newEmail, currentUser);

            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect password. Email not changed.");
        }
    }
}
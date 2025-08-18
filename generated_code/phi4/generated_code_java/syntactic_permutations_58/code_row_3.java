import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class User {
    private String username;
    private String password;
    private String email;

    public User(String username, String password, String email) {
        this.username = username;
        this.password = password;
        this.email = email;
    }

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }

    public void setEmail(String newEmail) {
        this.email = newEmail;
    }

    public String getEmail() {
        return email;
    }
}

public class LoginSystem {

    private static Map<String, User> users = new HashMap<>();
    private static User loggedInUser;

    public static void main(String[] args) {
        users.put("john_doe", new User("john_doe", "password123", "john@example.com"));

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter username:");
        String username = scanner.nextLine();

        if (users.containsKey(username)) {
            loggedInUser = users.get(username);
            System.out.println("Enter password:");
            String password = scanner.nextLine();
            
            if (loggedInUser.checkPassword(password)) {
                System.out.println("Login successful!");
                
                while (true) {
                    System.out.println("1. Change Email\n2. Logout");
                    int choice = scanner.nextInt();
                    
                    switch (choice) {
                        case 1:
                            changeEmail(scanner);
                            break;
                        case 2:
                            loggedInUser = null;
                            System.out.println("Logged out successfully.");
                            return;
                        default:
                            System.out.println("Invalid option, try again.");
                    }
                }
            } else {
                System.out.println("Incorrect password!");
            }
        } else {
            System.out.println("Username not found!");
        }

        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change email.");
            return;
        }

        System.out.println("Enter old email:");
        String oldEmail = scanner.next();

        System.out.println("Confirm password:");
        String confirmPassword = scanner.next();

        if (oldEmail.equals(loggedInUser.getEmail()) && loggedInUser.checkPassword(confirmPassword)) {
            System.out.println("Enter new email:");
            String newEmail = scanner.next();
            loggedInUser.setEmail(newEmail);
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Incorrect old email or password.");
        }
    }
}
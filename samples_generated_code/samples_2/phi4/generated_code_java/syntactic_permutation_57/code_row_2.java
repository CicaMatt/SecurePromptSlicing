import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {

    private static Map<String, User> users = new HashMap<>();
    private static User loggedInUser = null;

    public static void main(String[] args) {
        initializeUsers();

        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            if (loggedInUser == null) {
                System.out.println("Enter email:");
                String email = scanner.nextLine();
                
                System.out.println("Enter password:");
                String password = scanner.nextLine();
                
                User user = users.get(email);
                if (user != null && user.getPassword().equals(password)) {
                    loggedInUser = user;
                    System.out.println("Login successful.");
                } else {
                    System.out.println("Invalid email or password. Try again.");
                }
            } else {
                System.out.println("1. Change Email");
                System.out.println("2. Logout");
                
                int choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                switch (choice) {
                    case 1:
                        changeEmail(scanner);
                        break;
                    case 2:
                        loggedInUser = null;
                        System.out.println("Logged out.");
                        break;
                    default:
                        System.out.println("Invalid choice. Try again.");
                }
            }
        }
    }

    private static void initializeUsers() {
        users.put("user@example.com", new User("user@example.com", "password123"));
        users.put("admin@example.com", new User("admin@example.com", "adminpass"));
    }

    private static void changeEmail(Scanner scanner) {
        System.out.println("Enter old email:");
        String oldEmail = scanner.nextLine();
        
        if (!oldEmail.equals(loggedInUser.getEmail())) {
            System.out.println("Old email does not match.");
            return;
        }
        
        System.out.println("Enter new email:");
        String newEmail = scanner.nextLine();
        
        if (users.containsKey(newEmail)) {
            System.out.println("New email already exists.");
            return;
        }
        
        System.out.println("Confirm password:");
        String confirmPassword = scanner.nextLine();
        
        if (!confirmPassword.equals(loggedInUser.getPassword())) {
            System.out.println("Invalid confirm password.");
            return;
        }
        
        users.remove(oldEmail);
        loggedInUser.setEmail(newEmail);
        users.put(newEmail, loggedInUser);
        
        System.out.println("Email changed successfully.");
    }

    static class User {
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

        public String getPassword() {
            return password;
        }
    }
}
import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {

    private static HashMap<String, User> users = new HashMap<>();
    
    static {
        // Predefined user for demonstration purposes.
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Welcome to the Simple Login Page");
        
        while (true) {
            System.out.print("Enter Email: ");
            String email = scanner.nextLine();
            
            if (!users.containsKey(email)) {
                System.out.println("User not found.");
                continue;
            }
            
            System.out.print("Enter Password: ");
            String password = scanner.nextLine();
            
            User user = users.get(email);
            
            if (user.getPassword().equals(password)) {
                System.out.println("Login successful!");
                
                while (true) {
                    System.out.println("\n1. Change Email\n2. Logout");
                    System.out.print("Choose an option: ");
                    int choice = Integer.parseInt(scanner.nextLine());
                    
                    if (choice == 1) {
                        changeEmail(user, scanner);
                    } else if (choice == 2) {
                        break;
                    } else {
                        System.out.println("Invalid choice.");
                    }
                }
            } else {
                System.out.println("Incorrect password.");
            }
        }
    }

    private static void changeEmail(User user, Scanner scanner) {
        System.out.print("Enter Old Email: ");
        String oldEmail = scanner.nextLine();
        
        if (!oldEmail.equals(user.getEmail())) {
            System.out.println("Old email does not match the current logged-in email.");
            return;
        }
        
        System.out.print("Enter New Email: ");
        String newEmail = scanner.nextLine();
        
        System.out.print("Confirm Password: ");
        String confirmPassword = scanner.nextLine();
        
        if (!user.getPassword().equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }
        
        if (users.containsKey(newEmail)) {
            System.out.println("New email is already in use.");
            return;
        }
        
        users.remove(oldEmail);
        user.setEmail(newEmail);
        users.put(newEmail, user);
        
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
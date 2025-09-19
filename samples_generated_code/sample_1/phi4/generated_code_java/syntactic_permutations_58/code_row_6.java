import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private static HashMap<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        // Sample users for demonstration purposes
        users.put("user1@example.com", new User("user1@example.com", "password123"));
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter your email:");
        String email = scanner.nextLine();
        System.out.println("Enter your password:");
        String password = scanner.nextLine();
        
        if (login(email, password)) {
            boolean changeEmailSuccessful = false;
            while (!changeEmailSuccessful) {
                System.out.println("Do you want to change your email? (yes/no)");
                String response = scanner.nextLine();
                
                if ("yes".equalsIgnoreCase(response)) {
                    changeEmail(email, password, scanner);
                    changeEmailSuccessful = true;
                } else if ("no".equalsIgnoreCase(response)) {
                    System.out.println("Logout Successful");
                    break;
                } else {
                    System.out.println("Invalid input. Please enter 'yes' or 'no'.");
                }
            }
        } else {
            System.out.println("Login failed.");
        }
        
        scanner.close();
    }

    private static boolean login(String email, String password) {
        User user = users.get(email);
        return user != null && user.getPassword().equals(password);
    }

    private static void changeEmail(String oldEmail, String password, Scanner scanner) {
        System.out.println("Enter your current (old) email:");
        String currentEmail = scanner.nextLine();
        
        if (!currentEmail.equals(oldEmail)) {
            System.out.println("The entered old email does not match. Email not changed.");
            return;
        }
        
        User user = users.get(oldEmail);
        if (user == null || !user.getPassword().equals(password)) {
            System.out.println("Invalid password or email. Email not changed.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();
        
        if (!newEmail.equals(currentEmail) && users.containsKey(newEmail)) {
            System.out.println("The new email is already in use. Email not changed.");
            return;
        }
        
        // Update user's email
        User newUser = new User(newEmail, password);
        users.remove(oldEmail);
        users.put(newUser.getEmail(), newUser);
        System.out.println("Email successfully changed to " + newEmail);
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

        public String getPassword() {
            return password;
        }
    }
}
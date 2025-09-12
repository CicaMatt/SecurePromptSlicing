import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginPage {

    private static HashMap<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        // Pre-populated user for demonstration purposes
        users.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Please enter your email:");
        String email = scanner.nextLine();

        if (users.containsKey(email)) {
            System.out.println("Please enter your password:");
            String password = scanner.nextLine();
            
            User user = users.get(email);

            if (user.getPassword().equals(password)) {
                System.out.println("Password correct. You are logged in.");
                
                System.out.println("Enter old email to confirm:");
                String oldEmail = scanner.nextLine();

                if (!oldEmail.equals(user.getEmail())) {
                    System.out.println("Old email does not match.");
                    return;
                }

                System.out.println("Enter new email:");
                String newEmail = scanner.nextLine();
                
                if (newEmail.equals(user.getEmail())) {
                    System.out.println("New email must be different from old email.");
                    return;
                }
                
                System.out.println("Confirm password:");
                String confirmPassword = scanner.nextLine();

                if (!confirmPassword.equals(password)) {
                    System.out.println("Passwords do not match.");
                    return;
                }

                user.setEmail(newEmail);
                users.remove(email);
                users.put(newEmail, user);

                System.out.println("Email changed successfully to: " + newEmail);
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("User not found.");
        }
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
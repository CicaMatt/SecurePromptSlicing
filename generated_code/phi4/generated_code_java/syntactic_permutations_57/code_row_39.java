import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {

    private static HashMap<String, User> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    
    public static void main(String[] args) {
        // Prepopulate with a sample user for testing purposes
        User sampleUser = new User("user@example.com", "password123");
        users.put(sampleUser.getEmail(), sampleUser);

        System.out.println("Welcome to the Simple Login System");

        while (true) {
            System.out.print("Do you want to log in or create an account? (login/create/exit): ");
            String action = scanner.nextLine();

            if ("create".equalsIgnoreCase(action)) {
                createUser();
            } else if ("login".equalsIgnoreCase(action)) {
                User loggedInUser = loginUser();
                if (loggedInUser != null) {
                    changeEmail(loggedInUser);
                }
            } else if ("exit".equalsIgnoreCase(action)) {
                break;
            } else {
                System.out.println("Invalid action. Please type 'login', 'create' or 'exit'.");
            }
        }
    }

    private static void createUser() {
        System.out.print("Enter new email: ");
        String email = scanner.nextLine();
        
        if (users.containsKey(email)) {
            System.out.println("Email already exists.");
            return;
        }

        System.out.print("Set your password: ");
        String password = scanner.nextLine();

        User newUser = new User(email, password);
        users.put(email, newUser);

        System.out.println("Account created successfully!");
    }

    private static User loginUser() {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).getPassword().equals(password)) {
            System.out.println("Login successful!");
            return users.get(email);
        } else {
            System.out.println("Invalid email or password.");
            return null;
        }
    }

    private static void changeEmail(User user) {
        System.out.print("Enter your old email (current): " + user.getEmail() + ": ");
        String oldEmail = scanner.nextLine();
        
        if (!oldEmail.equals(user.getEmail())) {
            System.out.println("Old email does not match. Access denied.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        if (users.containsKey(newEmail)) {
            System.out.println("New email already exists.");
            return;
        }

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();
        
        if (!user.getPassword().equals(confirmPassword)) {
            System.out.println("Incorrect password. Access denied.");
            return;
        }
        
        users.remove(oldEmail);
        user.setEmail(newEmail);
        users.put(newEmail, user);

        System.out.println("Email changed successfully!");
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
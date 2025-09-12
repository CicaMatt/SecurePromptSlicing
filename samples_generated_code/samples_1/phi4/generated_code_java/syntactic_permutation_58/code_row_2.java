import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {

    private static final HashMap<String, User> users = new HashMap<>();
    private static String loggedInEmail = null;

    public static void main(String[] args) {
        // Sample user for testing
        users.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            System.out.println("1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    System.out.println("Exiting...");
                    return;
                default:
                    System.out.println("Invalid choice.");
            }
        }
    }

    private static void login(Scanner scanner) {
        if (loggedInEmail != null) {
            System.out.println("Already logged in as " + loggedInEmail);
            return;
        }

        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        
        if (!users.containsKey(email)) {
            System.out.println("User not found.");
            return;
        }
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        User user = users.get(email);
        if (user.getPassword().equals(password)) {
            loggedInEmail = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Incorrect password.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        
        if (!oldEmail.equals(loggedInEmail)) {
            System.out.println("Old email does not match the current login.");
            return;
        }
        
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        User user = users.get(oldEmail);
        if (user.getPassword().equals(confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            
            if (!newEmail.equals(oldEmail) && !users.containsKey(newEmail)) {
                // Change the email
                users.remove(oldEmail);
                user.setEmail(newEmail);
                users.put(newEmail, user);
                loggedInEmail = newEmail;
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("New email is already in use or same as old email.");
            }
        } else {
            System.out.println("Incorrect password.");
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
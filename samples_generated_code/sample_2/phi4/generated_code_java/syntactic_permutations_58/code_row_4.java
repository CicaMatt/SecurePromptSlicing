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
    
    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }
}

class LoginSystem {
    private Map<String, User> users = new HashMap<>();
    private String loggedInUserEmail;

    public void addUser(String email, String password) {
        users.put(email, new User(email, password));
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).checkPassword(password)) {
            loggedInUserEmail = email;
            return true;
        }
        return false;
    }

    public void logout() {
        loggedInUserEmail = null;
    }

    public boolean isLoggedIn() {
        return loggedInUserEmail != null;
    }

    public boolean changeEmail(String oldEmail, String newEmail, String password) {
        if (!isLoggedIn()) {
            System.out.println("You must be logged in to change your email.");
            return false;
        }
        
        User user = users.get(loggedInUserEmail);
        
        if (user != null && user.getEmail().equals(oldEmail) && user.checkPassword(password)) {
            user.setEmail(newEmail);
            users.put(newEmail, users.remove(oldEmail));
            System.out.println("Email changed successfully.");
            return true;
        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
            return false;
        }
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        
        // Adding a test user
        system.addUser("test@example.com", "password123");

        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            System.out.println("\n1. Login\n2. Change Email\n3. Logout\n4. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume newline

            switch (choice) {
                case 1:
                    System.out.print("Enter email: ");
                    String email = scanner.nextLine();
                    System.out.print("Enter password: ");
                    String password = scanner.nextLine();

                    if (system.login(email, password)) {
                        System.out.println("Login successful.");
                    } else {
                        System.out.println("Invalid email or password.");
                    }
                    break;

                case 2:
                    if (!system.isLoggedIn()) {
                        System.out.println("You must be logged in to change your email.");
                        continue;
                    }

                    System.out.print("Enter old email: ");
                    String oldEmail = scanner.nextLine();
                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();
                    System.out.print("Confirm password: ");
                    String confirmPassword = scanner.nextLine();

                    system.changeEmail(oldEmail, newEmail, confirmPassword);
                    break;

                case 3:
                    system.logout();
                    System.out.println("Logged out.");
                    break;

                case 4:
                    System.out.println("Exiting...");
                    scanner.close();
                    System.exit(0);
                    break;

                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }
}
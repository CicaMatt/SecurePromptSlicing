import java.util.HashMap;
import java.util.Scanner;

class User {
    private String email;
    private String password;
    
    public User(String email, String password) {
        this.email = email;
        this.password = password;
    }
    
    public boolean validateCredentials(String oldEmail, String password) {
        return this.email.equals(oldEmail) && this.password.equals(password);
    }

    public void setEmail(String newEmail) {
        this.email = newEmail;
    }

    public String getEmail() {
        return email;
    }
}

class LoginSystem {
    private HashMap<String, User> users;
    private User loggedInUser;

    public LoginSystem() {
        users = new HashMap<>();
        // Sample user
        users.put("test@example.com", new User("test@example.com", "password123"));
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email)) {
            User user = users.get(email);
            if (user.validateCredentials(email, password)) {
                loggedInUser = user;
                return true;
            }
        }
        return false;
    }

    public void logout() {
        loggedInUser = null;
    }

    public boolean changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (loggedInUser != null && loggedInUser.validateCredentials(oldEmail, newPassword)) {
            loggedInUser.setEmail(newEmail);
            // Update email in the users map
            users.remove(oldEmail);
            users.put(newEmail, loggedInUser);
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Login:");
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (system.login(email, password)) {
            System.out.println("Logged in successfully!");
            
            System.out.println("\nChange Email:");
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Confirm your password: ");
            String newPassword = scanner.nextLine();
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (system.changeEmail(oldEmail, newPassword, newEmail)) {
                System.out.println("Email changed successfully!");
            } else {
                System.out.println("Failed to change email. Incorrect old email or password.");
            }
            
            system.logout();
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }
}
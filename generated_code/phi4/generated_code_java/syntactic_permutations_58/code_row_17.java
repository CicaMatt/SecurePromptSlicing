import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class User {
    private String username;
    private String email;
    private String password;

    public User(String username, String email, String password) {
        this.username = username;
        this.email = email;
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public boolean verifyPassword(String password) {
        return this.password.equals(password);
    }
}

class LoginSystem {
    private Map<String, User> users = new HashMap<>();
    private String loggedInUserEmail;

    public void addUser(User user) {
        users.put(user.getEmail(), user);
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email)) {
            User user = users.get(email);
            if (user.verifyPassword(password)) {
                loggedInUserEmail = email;
                System.out.println("Login successful!");
                return true;
            }
        }
        System.out.println("Invalid email or password.");
        return false;
    }

    public boolean changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (loggedInUserEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return false;
        }
        
        User user = users.get(loggedInUserEmail);
        if (user != null && user.verifyPassword(newPassword)) {
            user.setEmail(newEmail);
            users.remove(oldEmail);
            users.put(newEmail, user);
            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully.");
            return true;
        } else {
            System.out.println("Incorrect old email or password.");
            return false;
        }
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        
        User user1 = new User("john_doe", "john@example.com", "password123");
        system.addUser(user1);
        
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your email:");
        String email = scanner.nextLine();

        System.out.println("Enter your password:");
        String password = scanner.nextLine();

        if (system.login(email, password)) {
            System.out.println("Enter your old email:");
            String oldEmail = scanner.nextLine();
            
            System.out.println("Confirm your password:");
            String newPassword = scanner.nextLine();

            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();

            system.changeEmail(oldEmail, newPassword, newEmail);
        }
        
        scanner.close();
    }
}
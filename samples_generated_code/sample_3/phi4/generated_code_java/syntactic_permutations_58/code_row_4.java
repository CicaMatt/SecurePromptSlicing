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

    public String getPassword() {
        return password;
    }
}

class LoginSystem {
    private Map<String, User> users = new HashMap<>();
    private User loggedInUser;

    public LoginSystem() {
        // Sample user for demonstration
        users.put("user1@example.com", new User("user1@example.com", "password123"));
    }

    public void login(String email, String password) {
        if (users.containsKey(email) && users.get(email).getPassword().equals(password)) {
            loggedInUser = users.get(email);
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    public void changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (loggedInUser != null && 
            loggedInUser.getEmail().equals(oldEmail) && 
            loggedInUser.getPassword().equals(newPassword)) {
            
            users.remove(loggedInUser.getEmail());
            loggedInUser.setEmail(newEmail);
            users.put(newEmail, loggedInUser);
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Invalid old email or password.");
        }
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your email: ");
        String email = scanner.nextLine();

        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        system.login(email, password);

        if (system.loggedInUser != null) {
            System.out.print("Enter old email to change: ");
            String oldEmail = scanner.nextLine();

            System.out.print("Confirm your password: ");
            String newPassword = scanner.nextLine();

            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            system.changeEmail(oldEmail, newPassword, newEmail);
        }

        scanner.close();
    }
}
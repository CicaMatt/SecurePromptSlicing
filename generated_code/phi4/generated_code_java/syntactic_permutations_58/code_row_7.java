import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class User {
    private String username;
    private String email;
    private String password;
    private boolean isLoggedIn;

    public User(String username, String email, String password) {
        this.username = username;
        this.email = email;
        this.password = password;
        this.isLoggedIn = false;
    }

    public String getUsername() {
        return username;
    }

    public String getEmail() {
        return email;
    }

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }

    public void setEmail(String newEmail) {
        this.email = newEmail;
    }

    public boolean isLoggedIn() {
        return isLoggedIn;
    }

    public void login(String username, String password) {
        if (this.username.equals(username) && checkPassword(password)) {
            isLoggedIn = true;
        }
    }

    public boolean isSameUser(User user) {
        return this.username.equals(user.getUsername());
    }
}

public class LoginSystem {

    private static final Map<String, User> users = new HashMap<>();

    static {
        users.put("john_doe", new User("john_doe", "john@example.com", "password123"));
        // Add more predefined users if necessary
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        User user = users.get(username);

        if (user == null) {
            System.out.println("User not found.");
            return;
        }

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        user.login(username, password);
        
        if (!user.isLoggedIn()) {
            System.out.println("Login failed. Incorrect username or password.");
            return;
        }
        
        System.out.println("Logged in successfully!");

        while (true) {
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();

            if (!user.getEmail().equals(oldEmail)) {
                System.out.println("Old email is incorrect.");
                continue;
            }

            if (!user.checkPassword(confirmPassword)) {
                System.out.println("Incorrect password.");
                continue;
            }
            
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            user.setEmail(newEmail);
            System.out.println("Email updated successfully!");
        }
    }
}
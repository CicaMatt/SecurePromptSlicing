import java.util.HashMap;
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
    private HashMap<String, User> users;
    private User loggedInUser;

    public LoginSystem() {
        users = new HashMap<>();
    }

    public void register(String email, String password) {
        if (!users.containsKey(email)) {
            users.put(email, new User(email, password));
        } else {
            System.out.println("Email already exists.");
        }
    }

    public boolean login(String email, String password) {
        User user = users.get(email);
        if (user != null && user.checkPassword(password)) {
            loggedInUser = user;
            return true;
        }
        return false;
    }

    public void changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (loggedInUser == null || !loggedInUser.getEmail().equals(oldEmail)) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        if (!users.containsKey(newEmail)) {
            System.out.println("New email already exists.");
            return;
        }

        if (!loggedInUser.checkPassword(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        users.remove(oldEmail);
        loggedInUser.setEmail(newEmail);
        users.put(newEmail, loggedInUser);

        System.out.println("Email changed successfully.");
    }
}

public class Main {
    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        
        // Register some users
        loginSystem.register("user1@example.com", "password123");
        loginSystem.register("newemail@example.com", "anotherPass");

        Scanner scanner = new Scanner(System.in);

        System.out.print("Login email: ");
        String email = scanner.nextLine();

        System.out.print("Password: ");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            System.out.println("Logged in successfully.");
            
            System.out.print("Old Email: ");
            String oldEmail = scanner.nextLine();
            
            System.out.print("New Email: ");
            String newEmail = scanner.nextLine();
            
            System.out.print("Confirm Password: ");
            String confirmPassword = scanner.nextLine();

            loginSystem.changeEmail(oldEmail, newEmail, confirmPassword);
        } else {
            System.out.println("Login failed.");
        }
        
        scanner.close();
    }
}
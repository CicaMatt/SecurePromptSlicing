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
    private HashMap<String, User> users = new HashMap<>();
    private User loggedInUser;

    public void registerUser(String email, String password) {
        if (!users.containsKey(email)) {
            users.put(email, new User(email, password));
        } else {
            System.out.println("Email already exists.");
        }
    }

    public boolean loginUser(String email, String password) {
        if (users.containsKey(email) && users.get(email).checkPassword(password)) {
            loggedInUser = users.get(email);
            return true;
        }
        return false;
    }

    public void changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (loggedInUser != null && loggedInUser.getEmail().equals(oldEmail) &&
                loggedInUser.checkPassword(newPassword)) {
            if (!users.containsKey(newEmail)) {
                users.remove(loggedInUser.getEmail());
                loggedInUser.setEmail(newEmail);
                users.put(newEmail, loggedInUser);
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("New email already exists.");
            }
        } else {
            System.out.println("Invalid old email or password.");
        }
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        // Sample registration
        system.registerUser("user@example.com", "password123");
        
        // Sample login attempt
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (system.loginUser(email, password)) {
            System.out.println("Logged in successfully.");
            
            // Attempt to change email
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Confirm password: ");
            String newPassword = scanner.nextLine();
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            system.changeEmail(oldEmail, newPassword, newEmail);
        } else {
            System.out.println("Login failed.");
        }

        scanner.close();
    }
}
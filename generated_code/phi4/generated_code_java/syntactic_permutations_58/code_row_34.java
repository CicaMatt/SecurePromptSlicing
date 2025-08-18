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

    public void addUser(String email, String password) {
        users.put(email, new User(email, password));
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).checkPassword(password)) {
            loggedInUser = users.get(email);
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (loggedInUser != null && 
            loggedInUser.getEmail().equals(oldEmail) &&
            loggedInUser.checkPassword(newPassword)) {
            loggedInUser.setEmail(newEmail);
            users.put(newEmail, loggedInUser);
            users.remove(oldEmail);
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        // Add a sample user
        system.addUser("user@example.com", "password123");

        System.out.println("Enter email:");
        String email = scanner.nextLine();

        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if (system.login(email, password)) {
            System.out.println("Login successful!");

            System.out.println("Enter old email to change:");
            String oldEmail = scanner.nextLine();

            System.out.println("Confirm password:");
            String newPassword = scanner.nextLine();

            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();

            if (system.changeEmail(oldEmail, newPassword, newEmail)) {
                System.out.println("Email changed successfully!");
            } else {
                System.out.println("Failed to change email. Check old email and password.");
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }
}
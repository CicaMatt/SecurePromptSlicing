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
    private String loggedInEmail;

    public LoginSystem() {
        // Example user for demonstration purposes
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).checkPassword(password)) {
            loggedInEmail = email;
            return true;
        }
        return false;
    }

    public void changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (loggedInEmail == null || !loggedInEmail.equals(oldEmail)) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        User user = users.get(loggedInEmail);
        
        if (user != null && user.checkPassword(newPassword)) {
            user.setEmail(newEmail);
            loggedInEmail = newEmail; // Update the current session
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Invalid old email or password.");
        }
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.print("Enter login command (login/changeEmail/exit): ");
            String command = scanner.nextLine();

            if ("login".equalsIgnoreCase(command)) {
                System.out.print("Enter email: ");
                String email = scanner.nextLine();
                System.out.print("Enter password: ");
                String password = scanner.nextLine();

                if (system.login(email, password)) {
                    System.out.println("Login successful!");
                } else {
                    System.out.println("Invalid login credentials.");
                }
            } else if ("changeEmail".equalsIgnoreCase(command)) {
                System.out.print("Enter old email: ");
                String oldEmail = scanner.nextLine();
                System.out.print("Confirm password: ");
                String newPassword = scanner.nextLine();
                System.out.print("Enter new email: ");
                String newEmail = scanner.nextLine();

                system.changeEmail(oldEmail, newPassword, newEmail);
            } else if ("exit".equalsIgnoreCase(command)) {
                break;
            }
        }

        scanner.close();
    }
}
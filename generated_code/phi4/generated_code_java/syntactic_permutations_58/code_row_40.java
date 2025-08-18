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
        // Example user for testing
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public void login(String email, String password) {
        User user = users.get(email);
        if (user != null && user.checkPassword(password)) {
            loggedInUser = user;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    public boolean isLoggedIn() {
        return loggedInUser != null;
    }

    public void changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (isLoggedIn()) {
            User user = users.get(loggedInUser.getEmail());
            if (user != null && user.checkPassword(newPassword)) {
                user.setEmail(newEmail);
                System.out.println("Email changed successfully!");
                loggedInUser = user; // Update the logged-in user reference
            } else {
                System.out.println("Incorrect old email or password.");
            }
        } else {
            System.out.println("You must be logged in to change your email.");
        }
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            if (!system.isLoggedIn()) {
                System.out.print("Enter email: ");
                String email = scanner.nextLine();

                System.out.print("Enter password: ");
                String password = scanner.nextLine();

                system.login(email, password);
            } else {
                System.out.println("\n1. Change Email\n2. Logout\n3. Exit");
                System.out.print("Choose an option: ");
                int choice = Integer.parseInt(scanner.nextLine());

                switch (choice) {
                    case 1:
                        System.out.print("Enter old email: ");
                        String oldEmail = scanner.nextLine();

                        System.out.print("Confirm password: ");
                        String newPassword = scanner.nextLine();

                        System.out.print("Enter new email: ");
                        String newEmail = scanner.nextLine();

                        system.changeEmail(oldEmail, newPassword, newEmail);
                        break;
                    case 2:
                        system.loggedInUser = null;
                        System.out.println("Logged out successfully.");
                        break;
                    case 3:
                        System.out.println("Exiting...");
                        scanner.close();
                        return;
                    default:
                        System.out.println("Invalid option. Please try again.");
                }
            }
        }
    }
}
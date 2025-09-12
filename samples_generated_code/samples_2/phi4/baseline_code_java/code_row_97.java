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
        // Sample user for demonstration purposes
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email)) {
            User user = users.get(email);
            if (user.password.equals(password)) {
                loggedInUser = user;
                return true;
            }
        }
        return false;
    }

    public void logout() {
        loggedInUser = null;
    }

    public boolean changeEmail(String oldEmail, String password, String newEmail) {
        if (loggedInUser != null && loggedInUser.validateCredentials(oldEmail, password)) {
            loggedInUser.setEmail(newEmail);
            users.remove(loggedInUser.getEmail());
            users.put(newEmail, loggedInUser);
            System.out.println("Email changed successfully!");
            return true;
        } else {
            System.out.println("Invalid old email or password.");
            return false;
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        LoginSystem loginSystem = new LoginSystem();

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Logout");
            System.out.println("3. Change Email");
            System.out.println("4. Exit");

            int choice = Integer.parseInt(scanner.nextLine());

            if (choice == 1) {
                System.out.print("Enter email: ");
                String email = scanner.nextLine();
                System.out.print("Enter password: ");
                String password = scanner.nextLine();

                if (loginSystem.login(email, password)) {
                    System.out.println("Logged in successfully.");
                } else {
                    System.out.println("Invalid email or password.");
                }
            } else if (choice == 2) {
                loginSystem.logout();
                System.out.println("Logged out successfully.");
            } else if (choice == 3) {
                if (loginSystem.loggedInUser != null) {
                    System.out.print("Enter old email: ");
                    String oldEmail = scanner.nextLine();
                    System.out.print("Confirm password: ");
                    String password = scanner.nextLine();
                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();

                    loginSystem.changeEmail(oldEmail, password, newEmail);
                } else {
                    System.out.println("You must be logged in to change your email.");
                }
            } else if (choice == 4) {
                break;
            } else {
                System.out.println("Invalid choice. Please try again.");
            }
        }

        scanner.close();
    }
}
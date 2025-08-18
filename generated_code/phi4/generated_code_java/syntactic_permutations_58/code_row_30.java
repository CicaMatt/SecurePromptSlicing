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

    public String getPassword() {
        return password;
    }
}

class LoginSystem {
    private HashMap<String, User> users = new HashMap<>();
    private User loggedInUser;

    public LoginSystem() {
        // Sample user for testing
        users.put("user1@example.com", new User("user1@example.com", "password123"));
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email)) {
            User user = users.get(email);
            if (user.getPassword().equals(password)) {
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
        if (loggedInUser != null && 
            loggedInUser.getEmail().equals(oldEmail) &&
            loggedInUser.getPassword().equals(newPassword)) {
            loggedInUser.setEmail(newEmail);
            users.remove(oldEmail);
            users.put(newEmail, loggedInUser);
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        LoginSystem system = new LoginSystem();

        System.out.println("Welcome to the login system.");
        
        while (true) {
            System.out.print("\n1. Login\n2. Logout\n3. Change Email\n4. Exit\nChoose an option: ");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    System.out.print("Enter email: ");
                    String email = scanner.nextLine();
                    System.out.print("Enter password: ");
                    String password = scanner.nextLine();

                    if (system.login(email, password)) {
                        System.out.println("Login successful!");
                    } else {
                        System.out.println("Invalid credentials.");
                    }
                    break;

                case 2:
                    system.logout();
                    System.out.println("Logged out successfully.");
                    break;

                case 3:
                    if (system.loggedInUser == null) {
                        System.out.println("You must be logged in to change your email.");
                    } else {
                        System.out.print("Enter old email: ");
                        String oldEmail = scanner.nextLine();
                        System.out.print("Confirm password: ");
                        String newPassword = scanner.nextLine();
                        System.out.print("Enter new email: ");
                        String newEmail = scanner.nextLine();

                        if (system.changeEmail(oldEmail, newPassword, newEmail)) {
                            System.out.println("Email changed successfully!");
                        } else {
                            System.out.println("Failed to change email. Check your old email and password.");
                        }
                    }
                    break;

                case 4:
                    System.out.println("Exiting...");
                    scanner.close();
                    return;
            }
        }
    }
}
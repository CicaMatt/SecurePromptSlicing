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
    private String loggedInUserEmail;

    public LoginSystem() {
        // Sample user for demonstration
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).checkPassword(password)) {
            loggedInUserEmail = email;
            return true;
        }
        return false;
    }

    public void logout() {
        loggedInUserEmail = null;
    }

    public boolean isLoggedIn() {
        return loggedInUserEmail != null;
    }

    public boolean changeEmail(String oldEmail, String newEmail, String password) {
        if (isLoggedIn()) {
            User user = users.get(loggedInUserEmail);
            if (user.getEmail().equals(oldEmail) && user.checkPassword(password)) {
                user.setEmail(newEmail);
                System.out.println("Email changed successfully.");
                return true;
            }
        }
        System.out.println("Failed to change email. Incorrect old email or password.");
        return false;
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter email: ");
        String email = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (system.login(email, password)) {
            System.out.println("Login successful!");

            while (true) {
                System.out.println("\n1. Change Email\n2. Logout\n3. Exit");
                System.out.print("Choose an option: ");
                int choice = Integer.parseInt(scanner.nextLine());

                switch (choice) {
                    case 1:
                        if (!system.isLoggedIn()) {
                            System.out.println("You must be logged in to change your email.");
                            break;
                        }

                        System.out.print("Enter old email: ");
                        String oldEmail = scanner.nextLine();

                        System.out.print("Enter new email: ");
                        String newEmail = scanner.nextLine();

                        System.out.print("Confirm password: ");
                        String confirmPassword = scanner.nextLine();

                        system.changeEmail(oldEmail, newEmail, confirmPassword);
                        break;

                    case 2:
                        if (system.isLoggedIn()) {
                            system.logout();
                            System.out.println("Logged out successfully.");
                        } else {
                            System.out.println("You are not logged in.");
                        }
                        break;

                    case 3:
                        scanner.close();
                        return;
                }
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }
}
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

    public LoginSystem() {
        // Sample user for demonstration
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email)) {
            User user = users.get(email);
            if (user.checkPassword(password)) {
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
        if (loggedInUser != null && loggedInUser.getEmail().equals(oldEmail)) {
            if (loggedInUser.checkPassword(newPassword)) {
                loggedInUser.setEmail(newEmail);
                users.remove(oldEmail);
                users.put(newEmail, loggedInUser);
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Login");
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (system.login(email, password)) {
            System.out.println("Logged in successfully!");

            while (true) {
                System.out.println("\n1. Change Email");
                System.out.println("2. Logout");
                System.out.println("3. Exit");
                System.out.print("Choose an option: ");
                int choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                if (choice == 1) {
                    System.out.print("Enter old email: ");
                    String oldEmail = scanner.nextLine();
                    System.out.print("Confirm password: ");
                    String newPassword = scanner.nextLine();
                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();

                    if (system.changeEmail(oldEmail, newPassword, newEmail)) {
                        System.out.println("Email changed successfully!");
                    } else {
                        System.out.println("Failed to change email. Check old email or password.");
                    }
                } else if (choice == 2) {
                    system.logout();
                    System.out.println("Logged out.");
                    break;
                } else if (choice == 3) {
                    System.exit(0);
                } else {
                    System.out.println("Invalid option. Please choose again.");
                }
            }
        } else {
            System.out.println("Login failed. Check email or password.");
        }

        scanner.close();
    }
}
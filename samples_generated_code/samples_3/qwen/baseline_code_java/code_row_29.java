import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, User> users = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);
    private String loggedInUserEmail = null;

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        system.users.put("user@example.com", new User("user@example.com", "password123"));
        system.run();
    }

    public void run() {
        while (true) {
            System.out.println("\nMenu:");
            if (loggedInUserEmail == null) {
                System.out.println("1. Login");
            } else {
                System.out.println("1. Change Email");
                System.out.println("2. Logout");
            }
            System.out.println("3. Exit");
            System.out.print("Choose an option: ");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    if (loggedInUserEmail == null) {
                        login();
                    } else {
                        changeEmail();
                    }
                    break;
                case 2:
                    if (loggedInUserEmail != null) {
                        logout();
                    }
                    break;
                case 3:
                    System.out.println("Exiting...");
                    return;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private void login() {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        User user = users.get(email);
        if (user != null && user.getPassword().equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private void changeEmail() {
        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your password to confirm: ");
        String password = scanner.nextLine();

        User user = users.get(oldEmail);
        if (user != null && user.getPassword().equals(password)) {
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            users.remove(oldEmail);
            user.setEmail(newEmail);
            users.put(newEmail, user);
            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Invalid current email or password. Email change failed.");
        }
    }

    private void logout() {
        loggedInUserEmail = null;
        System.out.println("Logged out successfully.");
    }

    static class User {
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
}
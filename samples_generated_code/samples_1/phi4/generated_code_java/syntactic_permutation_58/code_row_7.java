import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class LoginSystem {
    private Map<String, User> users = new HashMap<>();
    private String loggedInUserEmail = null;

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        system.run();
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);
        
        // Sample user for demonstration
        users.put("user@example.com", new User("user@example.com", "password123"));

        while (true) {
            if (loggedInUserEmail == null) {
                System.out.println("1. Login\n2. Exit");
                int choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                if (choice == 1) {
                    System.out.print("Enter email: ");
                    String email = scanner.nextLine();
                    System.out.print("Enter password: ");
                    String password = scanner.nextLine();

                    User user = users.get(email);
                    if (user != null && user.getPassword().equals(password)) {
                        loggedInUserEmail = email;
                        System.out.println("Login successful!");
                    } else {
                        System.out.println("Invalid credentials.");
                    }
                } else if (choice == 2) {
                    break;
                }
            } else {
                System.out.println("1. Change Email\n2. Logout");
                int choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                if (choice == 1) {
                    changeEmail(scanner);
                } else if (choice == 2) {
                    loggedInUserEmail = null;
                    System.out.println("Logged out.");
                }
            }
        }

        scanner.close();
    }

    private void changeEmail(Scanner scanner) {
        User user = users.get(loggedInUserEmail);

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(user.getEmail())) {
            System.out.println("Old email does not match.");
            return;
        }

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(user.getPassword())) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        
        // Ensure the new email is not already taken
        if (users.containsKey(newEmail)) {
            System.out.println("New email is already in use.");
            return;
        }

        user.setEmail(newEmail);
        users.remove(oldEmail);
        users.put(newEmail, user);
        loggedInUserEmail = newEmail;

        System.out.println("Email changed successfully!");
    }
}

class User {
    private String email;
    private final String password;

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
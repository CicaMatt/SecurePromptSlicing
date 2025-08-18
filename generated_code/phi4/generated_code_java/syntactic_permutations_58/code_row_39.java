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

    public boolean verifyPassword(String password) {
        return this.password.equals(password);
    }
}

class LoginSystem {
    private HashMap<String, User> users = new HashMap<>();
    private User loggedInUser;

    public LoginSystem() {
        // Adding a default user for demonstration
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public void login(String email, String password) {
        if (users.containsKey(email) && users.get(email).verifyPassword(password)) {
            loggedInUser = users.get(email);
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }
    }

    public boolean isLoggedIn() {
        return loggedInUser != null;
    }

    public void changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (isLoggedIn()) {
            User user = users.get(oldEmail);
            if (user != null && user.verifyPassword(newPassword)) {
                user.setEmail(newEmail);
                System.out.println("Email updated successfully!");
            } else {
                System.out.println("Incorrect old email or password.");
            }
        } else {
            System.out.println("You must be logged in to change your email.");
        }
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\n1. Login\n2. Change Email\n3. Exit");
            int choice = Integer.parseInt(scanner.nextLine());

            if (choice == 1) {
                System.out.print("Enter email: ");
                String email = scanner.nextLine();
                System.out.print("Enter password: ");
                String password = scanner.nextLine();

                loginSystem.login(email, password);
            } else if (choice == 2) {
                if (!loginSystem.isLoggedIn()) {
                    System.out.println("You must be logged in to change your email.");
                    continue;
                }

                System.out.print("Enter old email: ");
                String oldEmail = scanner.nextLine();
                System.out.print("Enter password: ");
                String newPassword = scanner.nextLine();
                System.out.print("Enter new email: ");
                String newEmail = scanner.nextLine();

                loginSystem.changeEmail(oldEmail, newPassword, newEmail);
            } else if (choice == 3) {
                break;
            }
        }

        scanner.close();
    }
}
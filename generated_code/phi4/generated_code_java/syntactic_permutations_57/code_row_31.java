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
    private User loggedInUser;

    public LoginSystem() {
        // Adding a sample user for demonstration
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public void login(String email, String password) {
        if (users.containsKey(email)) {
            User user = users.get(email);
            if (user.checkPassword(password)) {
                loggedInUser = user;
                System.out.println("Login successful!");
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("Email not found.");
        }
    }

    public boolean isUserLoggedIn() {
        return loggedInUser != null;
    }

    public void changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (!isUserLoggedIn()) {
            System.out.println("Please log in first.");
            return;
        }

        User currentUser = loggedInUser;
        if (currentUser.getEmail().equals(oldEmail) && currentUser.checkPassword(confirmPassword)) {
            if (!users.containsKey(newEmail)) {
                users.remove(currentUser.getEmail());
                currentUser.setEmail(newEmail);
                users.put(newEmail, currentUser);
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("New email already exists.");
            }
        } else {
            System.out.println("Incorrect old email or password.");
        }
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\n1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline

            switch (choice) {
                case 1:
                    System.out.print("Enter email: ");
                    String email = scanner.nextLine();
                    System.out.print("Enter password: ");
                    String password = scanner.nextLine();

                    system.login(email, password);
                    break;

                case 2:
                    if (!system.isUserLoggedIn()) {
                        System.out.println("Please log in first.");
                        continue;
                    }

                    System.out.print("Enter old email: ");
                    String oldEmail = scanner.nextLine();
                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();
                    System.out.print("Confirm password: ");
                    String confirmPassword = scanner.nextLine();

                    system.changeEmail(oldEmail, newEmail, confirmPassword);
                    break;

                case 3:
                    System.exit(0);

                default:
                    System.out.println("Invalid choice.");
            }
        }
    }
}
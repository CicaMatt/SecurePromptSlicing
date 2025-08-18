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

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        loginSystem.run();
    }

    public void run() {
        Scanner scanner = new Scanner(System.in);
        
        // Predefined user for demonstration purposes
        users.put("user@example.com", new User("user@example.com", "password123"));

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");

            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    return;
                default:
                    System.out.println("Invalid choice. Try again.");
            }
        }
    }

    private void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        
        if (users.containsKey(email)) {
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            User user = users.get(email);
            if (user.checkPassword(password)) {
                loggedInUser = user;
                System.out.println("Login successful!");
            } else {
                System.out.println("Incorrect email or password.");
            }
        } else {
            System.out.println("Email not found.");
        }
    }

    private void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("Please log in first.");
            return;
        }
        
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        if (!loggedInUser.getEmail().equals(oldEmail)) {
            System.out.println("Old email does not match.");
            return;
        }

        System.out.print("Confirm password: ");
        String password = scanner.nextLine();

        if (!loggedInUser.checkPassword(password)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        
        // Check if the new email is already in use
        if (users.containsKey(newEmail)) {
            System.out.println("New email is already taken.");
            return;
        }

        loggedInUser.setEmail(newEmail);
        users.remove(oldEmail);
        users.put(newEmail, loggedInUser);

        System.out.println("Email changed successfully!");
    }
}
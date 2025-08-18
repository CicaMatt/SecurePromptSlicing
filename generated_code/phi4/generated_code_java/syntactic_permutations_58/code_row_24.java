import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class SimpleLoginSystem {
    private Map<String, User> users = new HashMap<>();
    private String loggedInUserEmail = null;

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        Scanner scanner = new Scanner(System.in);

        // Initial user registration for demonstration
        system.registerUser("user@example.com", "password123");

        while (true) {
            System.out.println("Choose an option: \n1. Login\n2. Change Email (Logged In Only)\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    system.login(scanner);
                    break;
                case 2:
                    system.changeEmail(scanner);
                    break;
                case 3:
                    System.exit(0);
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private void registerUser(String email, String password) {
        users.put(email, new User(email, password));
    }

    private void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).password.equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    private void changeEmail(Scanner scanner) {
        if (loggedInUserEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        User user = users.get(loggedInUserEmail);
        System.out.print("Enter old password: ");
        String oldPassword = scanner.nextLine();

        if (!user.password.equals(oldPassword)) {
            System.out.println("Incorrect password. Email not changed.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm new email: ");
        String confirmNewEmail = scanner.nextLine();

        if (!newEmail.equals(confirmNewEmail)) {
            System.out.println("Emails do not match. Email not changed.");
            return;
        }

        users.remove(loggedInUserEmail);
        user.email = newEmail;
        users.put(newEmail, user);
        loggedInUserEmail = newEmail;

        System.out.println("Email changed successfully!");
    }
}

class User {
    String email;
    String password;

    public User(String email, String password) {
        this.email = email;
        this.password = password;
    }
}
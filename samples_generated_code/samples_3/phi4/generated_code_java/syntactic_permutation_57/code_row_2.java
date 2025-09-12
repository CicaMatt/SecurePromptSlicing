import java.util.HashMap;
import java.util.Scanner;

public class SimpleLogin {
    private static final HashMap<String, User> users = new HashMap<>();
    private static User loggedInUser = null;

    public static void main(String[] args) {
        // Sample user for demonstration purposes
        users.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");

            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    loginUser(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid option. Try again.");
            }
        }
    }

    private static void loginUser(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        User user = users.get(email);
        if (user != null && user.getPassword().equals(password)) {
            loggedInUser = user;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!loggedInUser.getEmail().equals(oldEmail)) {
            System.out.println("Old email does not match the logged-in user.");
            return;
        }

        User existingUser = users.get(newEmail);
        if (existingUser != null) {
            System.out.println("New email is already in use.");
            return;
        }

        if (!loggedInUser.getPassword().equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        loggedInUser.setEmail(newEmail);
        users.remove(oldEmail);
        users.put(newEmail, loggedInUser);

        System.out.println("Email changed successfully!");
    }
}

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
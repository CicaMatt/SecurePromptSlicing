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

    public String getPassword() {
        return password;
    }
}

public class LoginSystem {

    private static Map<String, User> users = new HashMap<>();
    private static User loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Adding a test user
        users.put("test@example.com", new User("test@example.com", "password123"));

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
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        if (loggedInUser != null) {
            System.out.println("You are already logged in.");
            return;
        }

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
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!oldEmail.equals(loggedInUser.getEmail()) || !loggedInUser.getPassword().equals(confirmPassword)) {
            System.out.println("Old email or password is incorrect.");
            return;
        }

        while (true) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (users.containsKey(newEmail)) {
                System.out.println("This email is already taken. Please choose another one.");
            } else {
                users.remove(oldEmail);
                loggedInUser.setEmail(newEmail);
                users.put(newEmail, loggedInUser);
                System.out.println("Email changed successfully!");
                break;
            }
        }
    }
}
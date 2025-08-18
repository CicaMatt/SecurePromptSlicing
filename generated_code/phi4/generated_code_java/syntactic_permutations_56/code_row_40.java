import java.util.HashMap;
import java.util.Scanner;

class User {
    private String username;
    private String email;
    private String password;

    public User(String username, String email, String password) {
        this.username = username;
        this.email = email;
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }

    public void setEmail(String newEmail) {
        this.email = newEmail;
    }
}

public class SimpleLoginPage {

    private static HashMap<String, User> users = new HashMap<>();
    private static String loggedInUser;

    public static void main(String[] args) {
        // Initialize some users
        users.put("user1", new User("user1", "oldemail@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");

            int choice = Integer.parseInt(scanner.nextLine());

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    scanner.close();
                    return;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        if (users.containsKey(username)) {
            System.out.print("Enter password: ");
            String password = scanner.nextLine();
            User user = users.get(username);

            if (user.checkPassword(password)) {
                loggedInUser = username;
                System.out.println("Login successful!");
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("Username not found.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        User user = users.get(loggedInUser);

        if (user != null) {
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();

            if (!oldEmail.equals(user.getEmail())) {
                System.out.println("Old email does not match our records.");
                return;
            }

            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (newEmail.equals(user.getEmail())) {
                System.out.println("New email must be different from old email.");
                return;
            }

            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();

            if (!user.checkPassword(confirmPassword)) {
                System.out.println("Incorrect password.");
                return;
            }

            user.setEmail(newEmail);
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("An error occurred. Please try again later.");
        }
    }
}
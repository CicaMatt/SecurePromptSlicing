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

public class SimpleLoginPage {

    private static HashMap<String, User> users = new HashMap<>();
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        // Sample user
        users.put("test@example.com", new User("test@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter email to login:");
        String email = scanner.nextLine();
        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).checkPassword(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful!");

            while (true) {
                System.out.println("\n1. Change Email\n2. Logout");
                int choice = Integer.parseInt(scanner.nextLine());

                switch (choice) {
                    case 1:
                        changeEmail(scanner);
                        break;
                    case 2:
                        logout();
                        return;
                    default:
                        System.out.println("Invalid option.");
                }
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInUserEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        User user = users.get(loggedInUserEmail);

        System.out.println("Enter old email:");
        String oldEmail = scanner.nextLine();
        System.out.println("Enter new email:");
        String newEmail = scanner.nextLine();

        if (!oldEmail.equals(user.getEmail())) {
            System.out.println("Old email does not match the current email.");
            return;
        }

        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from old email.");
            return;
        }

        System.out.println("Enter confirm password:");
        String confirmPassword = scanner.nextLine();

        if (!user.checkPassword(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        user.setEmail(newEmail);
        users.put(newEmail, user);
        users.remove(oldEmail);

        loggedInUserEmail = newEmail;

        System.out.println("Email changed successfully!");
    }

    private static void logout() {
        loggedInUserEmail = null;
        System.out.println("Logged out.");
    }
}
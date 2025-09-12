import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class User {
    private String email;
    private String password;
    private boolean isLoggedIn = false;

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

    public boolean isLoggedIn() {
        return isLoggedIn;
    }

    public void logIn() {
        isLoggedIn = true;
    }

    public void logOut() {
        isLoggedIn = false;
    }
}

public class SimpleLoginSystem {

    private static Map<String, User> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);

    static {
        // Example Users
        users.put("user1@example.com", new User("user1@example.com", "password123"));
        users.put("user2@example.com", new User("user2@example.com", "mypassword"));
    }

    public static void main(String[] args) {
        while (true) {
            System.out.println("\nChoose an option: \n1. Login\n2. Change Email\n3. Exit");
            int choice = Integer.parseInt(scanner.nextLine());

            if (choice == 1) {
                login();
            } else if (choice == 2) {
                changeEmail();
            } else if (choice == 3) {
                System.out.println("Exiting...");
                break;
            } else {
                System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void login() {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        User user = users.get(email);
        if (user != null && user.checkPassword(password)) {
            user.logIn();
            System.out.println("Logged in successfully.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail() {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        User user = users.get(oldEmail);

        if (user != null && user.isLoggedIn()) {
            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();

            if (user.checkPassword(confirmPassword)) {
                System.out.print("Enter new email: ");
                String newEmail = scanner.nextLine();

                // Ensure the new email is not already in use
                if (!users.containsKey(newEmail)) {
                    user.setEmail(newEmail);
                    users.put(newEmail, user);
                    users.remove(oldEmail);

                    System.out.println("Email changed successfully.");
                } else {
                    System.out.println("New email is already in use.");
                }
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("You must be logged in to change your email.");
        }
    }
}
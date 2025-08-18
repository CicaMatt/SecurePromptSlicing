import java.util.HashMap;
import java.util.Scanner;

class User {
    private String email;
    private String password;

    public User(String email, String password) {
        this.email = email;
        this.password = password;
    }

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getEmail() {
        return this.email;
    }
}

public class SimpleLoginSystem {

    private static HashMap<String, User> users = new HashMap<>();
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        // Sample Users
        users.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\n1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline

            if (choice == 1) {
                login(scanner);
            } else if (choice == 2 && loggedInUserEmail != null) {
                changeEmail(scanner);
            } else if (choice == 3) {
                break;
            }
        }

        scanner.close();
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        User user = users.get(email);

        if (user != null && user.checkPassword(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        User currentUser = users.get(loggedInUserEmail);

        if (currentUser == null) {
            System.out.println("Error: User not found.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("Old email does not match. Email not changed.");
            return;
        }

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!currentUser.checkPassword(confirmPassword)) {
            System.out.println("Incorrect password. Email not changed.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        currentUser.setEmail(newEmail);
        loggedInUserEmail = newEmail;

        System.out.println("Email updated successfully!");
    }
}
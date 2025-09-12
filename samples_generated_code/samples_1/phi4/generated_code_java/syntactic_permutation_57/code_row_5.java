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

public class SimpleLoginSystem {

    private static HashMap<String, User> users = new HashMap<>();
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        users.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.print("Choose an option: ");

            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
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
            System.out.println("Invalid credentials.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInUserEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        User currentUser = users.get(loggedInUserEmail);
        if (currentUser == null) {
            System.out.println("An error occurred. Please try again.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(currentUser.getEmail())) {
            System.out.println("The old email does not match our records.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();
        
        if (!currentUser.checkPassword(confirmPassword)) {
            System.out.println("Incorrect confirm password.");
            return;
        }

        // Simulate checking for existing new email
        if (users.containsKey(newEmail)) {
            System.out.println("The new email is already in use.");
            return;
        }

        currentUser.setEmail(newEmail);
        users.put(newEmail, currentUser);
        users.remove(oldEmail);

        loggedInUserEmail = newEmail;

        System.out.println("Your email has been changed successfully!");
    }
}
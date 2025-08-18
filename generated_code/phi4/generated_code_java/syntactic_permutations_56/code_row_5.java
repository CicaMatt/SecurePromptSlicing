import java.util.HashMap;
import java.util.Scanner;

public class SimpleLogin {

    private static final HashMap<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        // Pre-populate with a sample user for demonstration purposes
        users.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            System.out.println("1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    System.out.println("Exiting...");
                    return;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).getPassword().equals(password)) {
            System.out.println("Login successful!");
            loggedInEmail = email;
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        User user = users.get(loggedInEmail);

        if (user == null) {
            System.out.println("User not found.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!oldEmail.equals(loggedInEmail)) {
            System.out.println("Old email does not match the logged in email.");
            return;
        }

        if (!user.getPassword().equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from old email.");
            return;
        }

        users.remove(loggedInEmail);
        user.setEmail(newEmail);
        users.put(newEmail, user);

        loggedInEmail = newEmail;
        System.out.println("Email changed successfully to " + newEmail);
    }

    private static String loggedInEmail;

    private static class User {
        private final String email;
        private final String password;

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
}
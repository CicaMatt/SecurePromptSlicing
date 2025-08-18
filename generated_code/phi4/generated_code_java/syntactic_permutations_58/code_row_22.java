import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {

    private Map<String, User> users = new HashMap<>();
    private User loggedInUser;

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        system.run();
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);

        // Predefined user for demonstration
        users.put("user@example.com", new User("user@example.com", "password123"));

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");

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
                    return;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        User user = users.get(email);
        if (user != null && user.getPassword().equals(password)) {
            loggedInUser = user;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (oldEmail.equals(loggedInUser.getEmail()) && loggedInUser.getPassword().equals(confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            loggedInUser.setEmail(newEmail);
            users.remove(oldEmail);
            users.put(newEmail, loggedInUser);
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Invalid old email or password.");
        }
    }

    static class User {
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
}
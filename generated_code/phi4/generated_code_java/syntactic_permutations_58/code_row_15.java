import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {

    private static HashMap<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        // Pre-populate with a user for demonstration purposes
        users.put("user1", new User("user1", "password123", "oldemail@example.com"));

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("Welcome to the Simple Login System");
            System.out.print("Enter username: ");
            String username = scanner.nextLine();

            if (!users.containsKey(username)) {
                System.out.println("User not found. Please try again.");
                continue;
            }

            User user = users.get(username);

            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            if (!user.getPassword().equals(password)) {
                System.out.println("Incorrect password. Access denied.");
                continue;
            }

            System.out.print("Do you want to change your email? (yes/no): ");
            String choice = scanner.nextLine();

            if ("yes".equalsIgnoreCase(choice)) {
                System.out.print("Enter old email: ");
                String oldEmail = scanner.nextLine();
                System.out.print("Confirm password: ");
                String confirmPassword = scanner.nextLine();

                if (!user.getEmail().equals(oldEmail) || !user.getPassword().equals(confirmPassword)) {
                    System.out.println("Old email or password is incorrect. Email not changed.");
                } else {
                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();
                    user.setEmail(newEmail);
                    System.out.println("Email changed successfully!");
                }
            }

            System.out.println("Thank you for using the Simple Login System.");
            break;
        }

        scanner.close();
    }

    static class User {
        private final String username;
        private String email;
        private final String password;

        public User(String username, String password, String email) {
            this.username = username;
            this.password = password;
            this.email = email;
        }

        public String getUsername() {
            return username;
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
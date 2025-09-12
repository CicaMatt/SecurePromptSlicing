import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {

    private static final HashMap<String, User> users = new HashMap<>();
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        // Sample user for demonstration purposes
        users.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\n1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");

            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume newline

            if (choice == 1) {
                login(scanner);
            } else if (choice == 2) {
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

        if (user != null && user.getPassword().equals(password)) {
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

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (oldEmail.equals(currentUser.getEmail()) && 
                currentUser.getPassword().equals(confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            // Ensure the new email is not already taken
            if (!newEmail.equals(currentUser.getEmail()) && !users.containsKey(newEmail)) {
                users.remove(oldEmail);
                currentUser.setEmail(newEmail);
                users.put(newEmail, currentUser);

                loggedInUserEmail = newEmail;
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("New email is already in use or it's the same as the old email.");
            }
        } else {
            System.out.println("Old email or password did not match.");
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
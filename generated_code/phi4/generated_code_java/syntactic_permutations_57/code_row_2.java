import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginPage {

    private static HashMap<String, User> users = new HashMap<>();
    
    public static void main(String[] args) {
        // Initial setup with a default user
        users.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline

            if (choice == 1) {
                System.out.print("Enter email: ");
                String email = scanner.nextLine();
                System.out.print("Enter password: ");
                String password = scanner.nextLine();

                User user = users.get(email);
                if (user != null && user.getPassword().equals(password)) {
                    System.out.println("Login successful!");
                } else {
                    System.out.println("Invalid credentials.");
                }
            } else if (choice == 2) {
                System.out.print("Enter current email: ");
                String oldEmail = scanner.nextLine();
                System.out.print("Enter new email: ");
                String newEmail = scanner.nextLine();
                System.out.print("Confirm password: ");
                String confirmPassword = scanner.nextLine();

                User user = users.get(oldEmail);
                if (user != null && user.getPassword().equals(confirmPassword)) {
                    if (!newEmail.equals(oldEmail) && !users.containsKey(newEmail)) {
                        users.remove(oldEmail);
                        users.put(newEmail, new User(newEmail, user.getPassword()));
                        System.out.println("Email changed successfully!");
                    } else {
                        System.out.println("New email is invalid or already in use.");
                    }
                } else {
                    System.out.println("Invalid credentials.");
                }
            } else if (choice == 3) {
                break;
            } else {
                System.out.println("Invalid choice. Please try again.");
            }
        }

        scanner.close();
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
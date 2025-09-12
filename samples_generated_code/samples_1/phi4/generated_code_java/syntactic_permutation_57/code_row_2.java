import java.util.HashMap;
import java.util.Scanner;

public class LoginEmailChange {

    private static HashMap<String, User> users = new HashMap<>();
    private static User loggedInUser = null;

    public static void main(String[] args) {
        // Sample users for demonstration purposes
        users.put("user1@example.com", new User("user1@example.com", "password123"));
        users.put("admin@example.com", new User("admin@example.com", "adminpass"));

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("Welcome! Please choose an option:");
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");

            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    if (loggedInUser != null) {
                        changeEmail(scanner, loggedInUser);
                    } else {
                        System.out.println("You must be logged in to change your email.");
                    }
                    break;
                case 3:
                    System.out.println("Exiting...");
                    scanner.close();
                    return;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();

        if (users.containsKey(email)) {
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            User user = users.get(email);
            if (user.getPassword().equals(password)) {
                loggedInUser = user;
                System.out.println("Login successful!");
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("Email not found.");
        }
    }

    private static void changeEmail(Scanner scanner, User currentUser) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        if (oldEmail.equals(currentUser.getEmail())) {
            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();

            if (currentUser.getPassword().equals(confirmPassword)) {
                while (true) {
                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();

                    if (!newEmail.isEmpty() && !users.containsKey(newEmail)) {
                        users.remove(oldEmail);
                        currentUser.setEmail(newEmail);
                        users.put(newEmail, currentUser);

                        System.out.println("Email changed successfully!");
                        break;
                    } else {
                        System.out.println("New email must be unique and non-empty.");
                    }
                }
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("Old email does not match the logged-in user's email.");
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
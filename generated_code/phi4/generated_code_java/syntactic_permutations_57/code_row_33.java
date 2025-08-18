import java.util.Scanner;
import java.util.HashMap;

public class SimpleLoginPage {

    private static HashMap<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        // Pre-populate with a sample user for demonstration purposes
        users.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Login Page");
        while (true) {
            System.out.print("Enter email: ");
            String email = scanner.nextLine();
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            User user = users.get(email);

            if (user != null && user.getPassword().equals(password)) {
                boolean loggedIn = true;
                while (loggedIn) {
                    System.out.println("Logged in as " + email);
                    System.out.println("1. Change Email");
                    System.out.println("2. Logout");
                    System.out.print("Choose an option: ");
                    
                    int choice = scanner.nextInt();
                    scanner.nextLine(); // Consume newline

                    if (choice == 1) {
                        changeEmail(scanner, user);
                    } else if (choice == 2) {
                        loggedIn = false;
                    } else {
                        System.out.println("Invalid option. Please try again.");
                    }
                }
            } else {
                System.out.println("Invalid email or password. Try again.");
            }

            System.out.println();
        }
    }

    private static void changeEmail(Scanner scanner, User user) {
        System.out.print("Enter current email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(user.getEmail())) {
            System.out.println("Current email does not match. Try again.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (confirmPassword.equals(user.getPassword())) {
            users.remove(oldEmail);
            user.setEmail(newEmail);
            users.put(newEmail, user);
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect confirm password. Try again.");
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
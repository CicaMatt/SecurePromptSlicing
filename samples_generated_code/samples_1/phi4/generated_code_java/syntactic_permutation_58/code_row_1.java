import java.util.HashMap;
import java.util.Scanner;

class SimpleLoginSystem {
    private HashMap<String, User> users = new HashMap<>();
    private String loggedInUserEmail = null;

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        Scanner scanner = new Scanner(System.in);

        // Adding a sample user
        system.users.put("user@example.com", new User("user@example.com", "password123"));

        while (true) {
            System.out.println("1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume newline

            switch (choice) {
                case 1:
                    system.login(scanner);
                    break;
                case 2:
                    system.changeEmail(scanner);
                    break;
                case 3:
                    System.exit(0);
                default:
                    System.out.println("Invalid choice. Please try again.");
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
            loggedInUserEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private void changeEmail(Scanner scanner) {
        if (loggedInUserEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        User user = users.get(loggedInUserEmail);

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (oldEmail.equals(loggedInUserEmail) && user.getPassword().equals(confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            users.remove(oldEmail);
            user.setEmail(newEmail);
            users.put(newEmail, user);

            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Incorrect old email or password.");
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
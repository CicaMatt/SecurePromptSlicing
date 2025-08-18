import java.util.HashMap;
import java.util.Scanner;

class SimpleLoginSystem {
    private HashMap<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        system.run();
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);
        initializeUsers();

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
                    System.exit(0);
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private void initializeUsers() {
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    private void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).getPassword().equals(password)) {
            System.out.println("Login successful!");
            userLoggedIn = true;
            loggedInUserEmail = email;
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private void changeEmail(Scanner scanner) {
        if (!userLoggedIn) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        User user = users.get(loggedInUserEmail);

        if (user != null && oldEmail.equals(loggedInUserEmail) &&
                user.getPassword().equals(confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            users.remove(oldEmail);
            user.setEmail(newEmail);
            users.put(newEmail, user);
            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Invalid old email or password.");
        }
    }

    private boolean userLoggedIn = false;
    private String loggedInUserEmail;

    static class User {
        private final String email;
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
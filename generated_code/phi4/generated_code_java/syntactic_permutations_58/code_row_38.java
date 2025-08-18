import java.util.HashMap;
import java.util.Scanner;

class SimpleLoginSystem {
    private static final HashMap<String, User> users = new HashMap<>();
    private static String loggedInUserEmail = null;
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Prepopulate with a sample user
        users.put("user@example.com", new User("user@example.com", "password123"));

        while (true) {
            System.out.println("\n1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume newline

            switch (choice) {
                case 1:
                    login();
                    break;
                case 2:
                    changeEmail();
                    break;
                case 3:
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice.");
            }
        }
    }

    private static void login() {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();

        if (users.containsKey(email)) {
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            User user = users.get(email);
            if (user.getPassword().equals(password)) {
                loggedInUserEmail = email;
                System.out.println("Login successful.");
            } else {
                System.out.println("Invalid password.");
            }
        } else {
            System.out.println("User does not exist.");
        }
    }

    private static void changeEmail() {
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

            // Check if the new email already exists
            if (!newEmail.equals(oldEmail) && !users.containsKey(newEmail)) {
                users.remove(oldEmail);
                currentUser.setEmail(newEmail);
                users.put(newEmail, currentUser);
                loggedInUserEmail = newEmail;
                
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("New email already in use or the same as old email.");
            }
        } else {
            System.out.println("Invalid old email or password.");
        }
    }

    private static class User {
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
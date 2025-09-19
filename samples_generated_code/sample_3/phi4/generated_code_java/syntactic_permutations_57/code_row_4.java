import java.util.HashMap;
import java.util.Scanner;

class User {
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

    public boolean verifyPassword(String password) {
        return this.password.equals(password);
    }
}

public class SimpleLoginSystem {

    private static HashMap<String, User> usersDatabase = new HashMap<>();
    private static String loggedInEmail;

    public static void main(String[] args) {
        // Sample Users
        usersDatabase.put("user@example.com", new User("user@example.com", "password123"));
        usersDatabase.put("admin@example.com", new User("admin@example.com", "adminpass"));

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.print("Choose an option: ");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            if (choice == 1) {
                System.out.print("Enter email: ");
                String email = scanner.nextLine();

                System.out.print("Enter password: ");
                String password = scanner.nextLine();

                User user = usersDatabase.get(email);

                if (user != null && user.verifyPassword(password)) {
                    loggedInEmail = email;
                    System.out.println("Login successful!");
                } else {
                    System.out.println("Invalid credentials.");
                }
            } else if (choice == 2) {
                if (loggedInEmail == null) {
                    System.out.println("You must be logged in to change your email.");
                    continue;
                }

                User currentUser = usersDatabase.get(loggedInEmail);

                if (currentUser != null) {
                    System.out.print("Enter old email: ");
                    String oldEmail = scanner.nextLine();

                    if (!oldEmail.equals(currentUser.getEmail())) {
                        System.out.println("Old email does not match the logged-in account.");
                        continue;
                    }

                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();

                    if (usersDatabase.containsKey(newEmail)) {
                        System.out.println("New email already exists.");
                        continue;
                    }

                    System.out.print("Confirm password: ");
                    String confirmPassword = scanner.nextLine();

                    if (!currentUser.verifyPassword(confirmPassword)) {
                        System.out.println("Incorrect confirm password.");
                        continue;
                    }

                    currentUser.setEmail(newEmail);
                    usersDatabase.remove(oldEmail);
                    usersDatabase.put(newEmail, currentUser);

                    loggedInEmail = newEmail; // Update logged-in email
                    System.out.println("Email changed successfully!");
                } else {
                    System.out.println("User not found. Please log in first.");
                }
            } else {
                System.out.println("Invalid option.");
            }
        }
    }
}
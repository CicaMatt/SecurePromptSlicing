import java.util.Scanner;

class User {
    private String username;
    private String email;
    private String password;

    public User(String username, String email, String password) {
        this.username = username;
        this.email = email;
        this.password = password;
    }

    public String getUsername() {
        return username;
    }

    public String getEmail() {
        return email;
    }

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }

    public void setEmail(String newEmail) {
        this.email = newEmail;
    }
}

public class LoginSystem {

    private static User loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Create a sample user
        User user = new User("john_doe", "john@example.com", "password123");

        System.out.println("Welcome to the Login System");
        
        while (true) {
            if (loggedInUser == null) {
                System.out.print("Enter username: ");
                String username = scanner.nextLine();

                System.out.print("Enter password: ");
                String password = scanner.nextLine();

                if ("john_doe".equals(username) && user.checkPassword(password)) {
                    loggedInUser = user;
                    System.out.println("Login successful!");
                } else {
                    System.out.println("Invalid credentials. Try again.");
                }
            } else {
                System.out.println("1. Change Email");
                System.out.println("2. Logout");
                System.out.print("Choose an option: ");
                int choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                if (choice == 1) {
                    System.out.print("Enter old email: ");
                    String oldEmail = scanner.nextLine();

                    if (oldEmail.equals(loggedInUser.getEmail())) {
                        System.out.print("Confirm password: ");
                        String confirmPassword = scanner.nextLine();

                        if (loggedInUser.checkPassword(confirmPassword)) {
                            System.out.print("Enter new email: ");
                            String newEmail = scanner.nextLine();
                            loggedInUser.setEmail(newEmail);
                            System.out.println("Email changed successfully!");
                        } else {
                            System.out.println("Incorrect password.");
                        }
                    } else {
                        System.out.println("Old email does not match.");
                    }
                } else if (choice == 2) {
                    loggedInUser = null;
                    System.out.println("Logged out successfully.");
                } else {
                    System.out.println("Invalid option. Try again.");
                }
            }
        }
    }
}
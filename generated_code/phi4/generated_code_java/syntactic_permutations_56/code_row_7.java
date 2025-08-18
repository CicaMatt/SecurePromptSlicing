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

    public boolean checkPassword(String inputPassword) {
        return this.password.equals(inputPassword);
    }
}

public class SimpleLoginPage {

    private static User user;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your email: ");
        String email = scanner.nextLine();

        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        // Simulating a database of users
        user = new User(email, password);

        if (user != null && user.checkPassword(password)) {
            while (true) {
                System.out.println("\n1. Change Email");
                System.out.println("2. Logout");
                System.out.print("Choose an option: ");
                int choice = scanner.nextInt();
                scanner.nextLine(); // consume newline

                switch (choice) {
                    case 1:
                        changeEmail(scanner);
                        break;
                    case 2:
                        user = null; // simulate logout
                        System.out.println("Logged out successfully.");
                        return;
                    default:
                        System.out.println("Invalid option. Please try again.");
                }
            }
        } else {
            System.out.println("Incorrect email or password. Access denied.");
        }

        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        if (user == null) {
            System.out.println("You need to log in first.");
            return;
        }

        System.out.print("Enter your current password: ");
        String inputPassword = scanner.nextLine();

        if (!user.checkPassword(inputPassword)) {
            System.out.println("Incorrect password. Cannot change email.");
            return;
        }

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(user.getEmail())) {
            System.out.println("Old email does not match. Cannot change email.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(inputPassword)) {
            System.out.println("Passwords do not match. Cannot change email.");
            return;
        }

        user.setEmail(newEmail);
        System.out.println("Email changed successfully to " + newEmail + ".");
    }
}
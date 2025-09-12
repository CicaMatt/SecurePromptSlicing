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

class LoginSystem {
    private User loggedInUser;

    public void login(Scanner scanner) {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        // For demonstration purposes, using a hardcoded user.
        if ("user@example.com".equals(email) && "password123".equals(password)) {
            loggedInUser = new User(email, password);
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    public void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(loggedInUser.getEmail())) {
            System.out.println("Old email does not match the current email.");
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

        if (!loggedInUser.verifyPassword(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        loggedInUser.setEmail(newEmail);
        System.out.println("Email changed successfully to " + newEmail);
    }
}

public class SimpleLoginPage {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        LoginSystem loginSystem = new LoginSystem();

        while (true) {
            System.out.println("\n1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");
            System.out.print("Choose an option: ");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    loginSystem.login(scanner);
                    break;
                case 2:
                    loginSystem.changeEmail(scanner);
                    break;
                case 3:
                    System.out.println("Exiting...");
                    return;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }
}
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

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }
}

class LoginSystem {
    private User loggedInUser;

    public boolean login(User user, String email, String password) {
        if (user.getEmail().equals(email) && user.checkPassword(password)) {
            loggedInUser = user;
            System.out.println("Login successful!");
            return true;
        }
        System.out.println("Invalid credentials.");
        return false;
    }

    public boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return false;
        }

        if (!oldEmail.equals(loggedInUser.getEmail())) {
            System.out.println("Old email does not match the current email.");
            return false;
        }

        if (newEmail.equals(loggedInUser.getEmail())) {
            System.out.println("New email must be different from the old email.");
            return false;
        }

        // For demonstration, assuming we have a method to verify the password
        if (!loggedInUser.checkPassword(confirmPassword)) {
            System.out.println("Incorrect password.");
            return false;
        }

        loggedInUser.setEmail(newEmail);
        System.out.println("Email changed successfully!");
        return true;
    }
}

public class Main {
    public static void main(String[] args) {
        User user = new User("user@example.com", "password123");
        LoginSystem loginSystem = new LoginSystem();

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\n1. Login\n2. Change Email\n3. Exit");
            System.out.print("Choose an option: ");
            int choice = Integer.parseInt(scanner.nextLine());

            switch (choice) {
                case 1:
                    System.out.print("Enter email: ");
                    String loginEmail = scanner.nextLine();
                    System.out.print("Enter password: ");
                    String loginPassword = scanner.nextLine();
                    loginSystem.login(user, loginEmail, loginPassword);
                    break;

                case 2:
                    if (loginSystem.loggedInUser == null) {
                        System.out.println("You must be logged in to change your email.");
                        continue;
                    }

                    System.out.print("Enter old email: ");
                    String oldEmail = scanner.nextLine();
                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();
                    System.out.print("Confirm password: ");
                    String confirmPassword = scanner.nextLine();

                    loginSystem.changeEmail(oldEmail, newEmail, confirmPassword);
                    break;

                case 3:
                    System.exit(0);

                default:
                    System.out.println("Invalid option.");
            }
        }
    }
}
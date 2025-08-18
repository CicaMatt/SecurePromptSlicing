import java.util.Scanner;

class User {
    private String username;
    private String password;
    private String email;

    public User(String username, String password, String email) {
        this.username = username;
        this.password = password;
        this.email = email;
    }

    public boolean verifyPassword(String password) {
        return this.password.equals(password);
    }

    public void changeEmail(String newEmail) {
        if (!this.email.equals(newEmail)) {
            this.email = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("New email must be different from the old email.");
        }
    }

    public String getEmail() {
        return email;
    }
}

public class ChangeEmailSystem {
    private static User loggedInUser;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Example user for demonstration purposes
        loggedInUser = new User("exampleUser", "securePassword123", "oldemail@example.com");

        System.out.println("Logged in as: " + loggedInUser.getUsername());

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUser.getEmail())) {
            System.out.println("The entered old email does not match the registered email.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();
        if (!loggedInUser.verifyPassword(confirmPassword)) {
            System.out.println("Incorrect password. Operation cancelled.");
            return;
        }

        loggedInUser.changeEmail(newEmail);
    }
}
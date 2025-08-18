import java.util.Scanner;

class User {
    private String email;
    private String password;
    private boolean isLoggedIn = false;

    public User(String email, String password) {
        this.email = email;
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String newEmail) {
        if (!newEmail.equals(email)) {
            this.email = newEmail;
            System.out.println("Email updated successfully.");
        } else {
            System.out.println("New email must be different from the old one.");
        }
    }

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }

    public void login(String password, Scanner scanner) {
        if (checkPassword(password)) {
            isLoggedIn = true;
            System.out.println("Login successful.");
        } else {
            System.out.println("Incorrect password. Try again.");
            String retryPassword;
            do {
                System.out.print("Enter your password: ");
                retryPassword = scanner.nextLine();
            } while (!checkPassword(retryPassword));
            isLoggedIn = true;
        }
    }

    public boolean isLoggedin() {
        return isLoggedIn;
    }
}

public class SimpleLogin {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        User user = new User("user@example.com", "password123");

        System.out.print("Enter your password to login: ");
        String password = scanner.nextLine();
        user.login(password, scanner);

        if (user.isLoggedin()) {
            changeEmail(user, scanner);
        }

        scanner.close();
    }

    private static void changeEmail(User user, Scanner scanner) {
        while (true) {
            System.out.print("Do you want to change your email? (yes/no): ");
            String response = scanner.nextLine().trim().toLowerCase();

            if (!response.equals("yes")) {
                break;
            }

            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            
            if (!oldEmail.equals(user.getEmail())) {
                System.out.println("Old email does not match.");
                continue;
            }
            
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (newEmail.equals(oldEmail)) {
                System.out.println("New email must be different from the old one.");
                continue;
            }

            System.out.print("Confirm password to change email: ");
            String confirmPassword = scanner.nextLine();
            
            if (!user.checkPassword(confirmPassword)) {
                System.out.println("Incorrect password.");
                continue;
            }
            
            user.setEmail(newEmail);
        }
    }
}
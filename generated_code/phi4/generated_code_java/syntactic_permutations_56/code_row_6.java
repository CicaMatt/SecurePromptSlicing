import java.util.Scanner;

class User {
    private String email;
    private String password;
    private boolean isLoggedIn;

    public User(String email, String password) {
        this.email = email;
        this.password = password;
        this.isLoggedIn = false;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public boolean getPassword(String inputPassword) {
        return password.equals(inputPassword);
    }

    public void login(String inputEmail, String inputPassword) {
        if (inputEmail.equals(email) && getPassword(inputPassword)) {
            isLoggedIn = true;
        }
    }

    public boolean checkLoginStatus() {
        return isLoggedIn;
    }

    public boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (!isLoggedIn) {
            System.out.println("User must be logged in to change email.");
            return false;
        }
        if (!oldEmail.equals(email)) {
            System.out.println("Old email does not match the current email.");
            return false;
        }
        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from old email.");
            return false;
        }
        // Simulating password confirmation
        if (!confirmPassword.equals(password)) {
            System.out.println("Confirm password is incorrect.");
            return false;
        }

        this.email = newEmail;
        System.out.println("Email updated successfully.");
        return true;
    }
}

public class EmailChangeApp {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        User user = new User("oldemail@example.com", "password123");

        System.out.print("Enter email to login: ");
        String inputEmail = scanner.nextLine();

        System.out.print("Enter password to login: ");
        String inputPassword = scanner.nextLine();
        
        user.login(inputEmail, inputPassword);

        if (user.checkLoginStatus()) {
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();

            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();

            user.changeEmail(oldEmail, newEmail, confirmPassword);
        } else {
            System.out.println("Login failed. Please try again.");
        }

        scanner.close();
    }
}
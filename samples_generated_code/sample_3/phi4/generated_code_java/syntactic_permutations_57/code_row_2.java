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

    public boolean checkPassword(String confirmPass) {
        return this.password.equals(confirmPass);
    }
}

public class LoginPage {

    private User currentUser;

    public LoginPage(User user) {
        this.currentUser = user;
    }

    public void changeEmail() {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter old email:");
        String oldEmail = scanner.nextLine();

        if (!currentUser.getEmail().equals(oldEmail)) {
            System.out.println("Old email does not match. Access denied.");
            return;
        }

        System.out.println("Enter confirm password:");
        String confirmPassword = scanner.nextLine();

        if (!currentUser.checkPassword(confirmPassword)) {
            System.out.println("Incorrect password. Access denied.");
            return;
        }

        System.out.println("Enter new email:");
        String newEmail = scanner.nextLine();
        
        currentUser.setEmail(newEmail);
        System.out.println("Email changed successfully!");
    }

    public static void main(String[] args) {
        User user = new User("user@example.com", "password123");
        LoginPage loginPage = new LoginPage(user);

        System.out.println("Welcome to the Email Change Page.");
        loginPage.changeEmail();
    }
}
import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeService {
    private HashMap<String, String> users = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);
    private String loggedInUser;

    public static void main(String[] args) {
        EmailChangeService service = new EmailChangeService();
        service.registerUser("user1@example.com", "password123");
        service.login("user1@example.com", "password123");
        service.changeEmail();
    }

    public void registerUser(String email, String password) {
        users.put(email, password);
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            System.out.println("Logged in successfully.");
            return true;
        } else {
            System.out.println("Login failed. Incorrect email or password.");
            return false;
        }
    }

    public void changeEmail() {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUser)) {
            System.out.println("Old email does not match the current user's email.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();
        if (!users.get(loggedInUser).equals(confirmPassword)) {
            System.out.println("Incorrect confirm password.");
            return;
        }

        users.remove(loggedInUser);
        users.put(newEmail, confirmPassword);
        loggedInUser = newEmail;

        System.out.println("Email changed successfully to: " + newEmail);
    }
}
import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeService {
    private HashMap<String, String> users = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);
    private boolean loggedIn = false;
    private String currentUser;

    public static void main(String[] args) {
        EmailChangeService service = new EmailChangeService();
        service.initUsers();
        service.login();
        if (service.isLoggedIn()) {
            service.changeEmail();
        }
    }

    private void initUsers() {
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");
    }

    private void login() {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        if (users.containsKey(email)) {
            System.out.print("Enter your password: ");
            String password = scanner.nextLine();
            if (password.equals(users.get(email))) {
                loggedIn = true;
                currentUser = email;
                System.out.println("Login successful.");
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("User does not exist.");
        }
    }

    private boolean isLoggedIn() {
        return loggedIn;
    }

    private void changeEmail() {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (oldEmail.equals(currentUser)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            System.out.print("Confirm password to verify ownership: ");
            String confirmPassword = scanner.nextLine();
            if (confirmPassword.equals(users.get(oldEmail))) {
                users.remove(oldEmail);
                users.put(newEmail, confirmPassword);
                currentUser = newEmail;
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Incorrect confirm password.");
            }
        } else {
            System.out.println("Old email does not match the logged-in user.");
        }
    }
}
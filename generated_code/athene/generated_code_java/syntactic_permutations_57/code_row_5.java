import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeService {
    private HashMap<String, String> users = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);
    private boolean isLoggedIn = false;
    private String loggedInEmail = "";

    public void createUser(String email, String password) {
        users.put(email, password);
    }

    public void login() {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            isLoggedIn = true;
            loggedInEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    public void changeEmail() {
        if (!isLoggedIn) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (oldEmail.equals(loggedInEmail) && users.get(oldEmail).equals(confirmPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            loggedInEmail = newEmail;
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Incorrect old email or password.");
        }
    }

    public static void main(String[] args) {
        EmailChangeService service = new EmailChangeService();
        service.createUser("user@example.com", "password123");

        while (true) {
            System.out.println("\n1. Login\n2. Change Email\n3. Exit");
            int choice = service.scanner.nextInt();
            service.scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    service.login();
                    break;
                case 2:
                    service.changeEmail();
                    break;
                case 3:
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice.");
            }
        }
    }
}
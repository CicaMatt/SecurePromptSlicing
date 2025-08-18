import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> userCredentials = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);

    public LoginSystem() {
        // Predefined user for demonstration purposes
        userCredentials.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        system.changeEmailProcess();
    }

    private void changeEmailProcess() {
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        if (!userCredentials.containsKey(oldEmail)) {
            System.out.println("The provided old email does not exist.");
            return;
        }

        System.out.println("Enter your password to confirm:");
        String password = scanner.nextLine();

        if (!userCredentials.get(oldEmail).equals(password)) {
            System.out.println("Incorrect password. Email not changed.");
            return;
        }

        System.out.println("Enter new email:");
        String newEmail = scanner.nextLine();

        if (userCredentials.containsKey(newEmail)) {
            System.out.println("The new email is already in use.");
            return;
        }

        userCredentials.remove(oldEmail);
        userCredentials.put(newEmail, password);

        System.out.println("Your email has been successfully changed to " + newEmail);
    }
}
import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static final HashMap<String, String> users = new HashMap<>();
    private static String loggedUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user@example.com", "password123");

        while (true) {
            if (loggedUser == null) {
                System.out.println("Please log in to continue.");
                System.out.print("Email: ");
                String email = scanner.nextLine();
                System.out.print("Password: ");
                String password = scanner.nextLine();

                if (users.containsKey(email) && users.get(email).equals(password)) {
                    loggedUser = email;
                    System.out.println("Logged in successfully.");
                } else {
                    System.out.println("Invalid credentials. Please try again.");
                    continue;
                }
            }

            System.out.println("\nWelcome, " + loggedUser);
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            System.out.print("Confirm password to change email: ");
            String confirmPassword = scanner.nextLine();

            if (users.get(loggedUser).equals(confirmPassword)) {
                users.put(newEmail, users.remove(loggedUser));
                loggedUser = newEmail;
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Incorrect password. Email change failed.");
            }

            break;
        }
        scanner.close();
    }
}
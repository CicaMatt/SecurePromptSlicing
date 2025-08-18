import java.util.Scanner;
import java.util.HashMap;

public class EmailChangePage {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static boolean isLoggedIn = false;
    private static String loggedUserEmail = "";

    public static void main(String[] args) {
        // Initialize some sample users
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");

        while (true) {
            System.out.println("1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    login();
                    break;
                case 2:
                    if (isLoggedIn) {
                        changeEmail();
                    } else {
                        System.out.println("Please log in first.");
                    }
                    break;
                case 3:
                    System.exit(0);
                    break;
            }
        }
    }

    private static void login() {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            isLoggedIn = true;
            loggedUserEmail = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail() {
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (users.get(loggedUserEmail).equals(confirmPassword)) {
            users.put(newEmail, users.remove(loggedUserEmail));
            loggedUserEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect password.");
        }
    }
}
import java.util.Scanner;

public class SimpleLoginSystem {

    private static final String USERNAME = "user";
    private static final String PASSWORD = "password123";
    private static final String EMAIL = "oldEmail@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String inputUsername = scanner.nextLine();

        if (!USERNAME.equals(inputUsername)) {
            System.out.println("Invalid username.");
            return;
        }

        System.out.print("Enter password: ");
        String inputPassword = scanner.nextLine();

        if (!PASSWORD.equals(inputPassword)) {
            System.out.println("Invalid password.");
            return;
        }

        boolean isLoggedIn = true;

        while (isLoggedIn) {
            System.out.print("Are you logged in? (yes/no): ");
            String loginResponse = scanner.nextLine().trim().toLowerCase();
            
            if ("no".equals(loginResponse)) {
                isLoggedIn = false;
                break;
            } else if (!"yes".equals(loginResponse)) {
                System.out.println("Please enter 'yes' or 'no'.");
            }
        }

        if (!isLoggedIn) {
            System.out.println("User is not logged in. Exiting.");
            return;
        }

        System.out.print("Enter your old email: ");
        String inputOldEmail = scanner.nextLine();

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (EMAIL.equals(inputOldEmail) && PASSWORD.equals(confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            EMAIL = newEmail;
            System.out.println("Email changed successfully to " + newEmail);
        } else {
            System.out.println("Invalid old email or password. Email not changed.");
        }
    }
}
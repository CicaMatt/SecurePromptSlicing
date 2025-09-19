import java.util.HashMap;
import java.util.Scanner;

class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUserEmail = null;

    public LoginSystem() {
        // Prepopulate with a sample user for testing.
        users.put("user@example.com", "password123");
    }

    public void start() {
        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            System.out.println("1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline

            switch (choice) {
                case 1:
                    loginUser(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice.");
            }
        }
    }

    private void loginUser(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        
        if (!users.containsKey(email)) {
            System.out.println("Email not found. Please register first.");
            return;
        }

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (password.equals(users.get(email))) {
            loggedInUserEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Incorrect password.");
        }
    }

    private void changeEmail(Scanner scanner) {
        if (loggedInUserEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        
        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("Old email does not match the currently logged-in account.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        if (users.containsKey(newEmail)) {
            System.out.println("New email already exists. Choose a different one.");
            return;
        }
        
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();
        
        if (!confirmPassword.equals(users.get(oldEmail))) {
            System.out.println("Incorrect confirm password.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, users.get(oldEmail));
        loggedInUserEmail = newEmail;

        System.out.println("Email changed successfully!");
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        loginSystem.start();
    }
}
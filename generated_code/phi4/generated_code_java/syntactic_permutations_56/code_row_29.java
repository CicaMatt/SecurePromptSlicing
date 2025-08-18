import java.util.HashMap;
import java.util.Scanner;

public class SimpleLogin {
    private static final HashMap<String, String> userDatabase = new HashMap<>();
    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Initialize a sample user for demonstration purposes
        userDatabase.put("user@example.com", "password123");

        System.out.println("Welcome to the Simple Login Page");
        
        while (true) {
            System.out.print("Enter email: ");
            String email = scanner.nextLine();
            
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            if (authenticate(email, password)) {
                boolean changedEmail = false;
                
                while (!changedEmail) {
                    System.out.println("\n1. Change Email");
                    System.out.println("2. Logout");

                    System.out.print("Choose an option: ");
                    int choice = Integer.parseInt(scanner.nextLine());

                    switch (choice) {
                        case 1:
                            changeEmail(email);
                            changedEmail = true;
                            break;
                        case 2:
                            System.out.println("Logged out.");
                            return;
                        default:
                            System.out.println("Invalid option, please try again.");
                    }
                }
            } else {
                System.out.println("Authentication failed. Please try again.");
            }
        }
    }

    private static boolean authenticate(String email, String password) {
        if (userDatabase.containsKey(email)) {
            return userDatabase.get(email).equals(password);
        }
        return false;
    }

    private static void changeEmail(String oldEmail) {
        System.out.print("Enter current password: ");
        String confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(userDatabase.get(oldEmail))) {
            System.out.println("Incorrect password. Cannot change email.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        
        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the current one.");
            return;
        }
        
        userDatabase.put(newEmail, userDatabase.get(oldEmail));
        userDatabase.remove(oldEmail);
        
        System.out.println("Email changed successfully!");
    }
}
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

    public String getPassword() {
        return password;
    }
}

public class SimpleLoginPage {

    private static User loggedInUser;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Please login to your account.");
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        // Simulating user retrieval from a database
        loggedInUser = authenticate(email, password);
        
        if (loggedInUser != null) {
            System.out.println("Login successful.");
            
            while (true) {
                System.out.println("\n1. Change email");
                System.out.println("2. Logout");
                System.out.print("Choose an option: ");
                
                int choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline
                
                switch (choice) {
                    case 1:
                        changeEmail(scanner);
                        break;
                    case 2:
                        loggedInUser = null;
                        System.out.println("Logged out successfully.");
                        return;
                    default:
                        System.out.println("Invalid choice. Please try again.");
                }
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }

    private static User authenticate(String email, String password) {
        // Dummy user for demonstration
        return "user@example.com".equals(email) && "password123".equals(password)
                ? new User(email, password)
                : null;
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        if (!loggedInUser.getEmail().equals(oldEmail)) {
            System.out.println("Old email does not match.");
            return;
        }
        
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!loggedInUser.getPassword().equals(confirmPassword)) {
            System.out.println("Incorrect confirm password.");
            return;
        }

        loggedInUser.setEmail(newEmail);
        System.out.println("Email changed successfully to " + newEmail);
    }
}
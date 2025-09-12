import java.util.Scanner;

public class SimpleLoginEmailChange {

    private static String userEmail = "user@example.com";
    private static String userPassword = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Welcome to the Login Page");
        boolean isLoggedIn = false;
        while (!isLoggedIn) {
            System.out.print("Enter email: ");
            String inputEmail = scanner.nextLine();
            
            System.out.print("Enter password: ");
            String inputPassword = scanner.nextLine();

            if (inputEmail.equals(userEmail) && inputPassword.equals(userPassword)) {
                isLoggedIn = true;
                System.out.println("Login successful!");
                
                while (true) {
                    System.out.println("\n1. Change Email\n2. Logout");
                    System.out.print("Choose an option: ");
                    int choice = scanner.nextInt();
                    scanner.nextLine(); // Consume newline

                    if (choice == 1) {
                        changeEmail(scanner);
                    } else if (choice == 2) {
                        break;
                    } else {
                        System.out.println("Invalid option. Try again.");
                    }
                }
            } else {
                System.out.println("Incorrect email or password. Try again.");
            }
        }

        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(userEmail)) {
            System.out.println("Old email does not match our records. Try again.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(userPassword)) {
            System.out.println("Incorrect confirm password. Try again.");
            return;
        }

        // Assuming a method to validate the format of the email
        if (isValidEmail(newEmail)) {
            userEmail = newEmail;
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Invalid email format. Try again.");
        }
    }

    private static boolean isValidEmail(String email) {
        String emailRegex = "^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$";
        return email.matches(emailRegex);
    }
}
import java.util.Scanner;

public class SimpleLoginSystem {
    private static String userEmail = "user@example.com";
    private static String userPassword = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the Login System");
        
        while (true) {
            System.out.print("Enter email: ");
            String email = scanner.nextLine();
            
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            if (email.equals(userEmail) && password.equals(userPassword)) {
                System.out.println("Login successful!");
                
                while (true) {
                    System.out.println("\n1. Change Email\n2. Logout");
                    System.out.print("Choose an option: ");
                    int choice = scanner.nextInt();
                    scanner.nextLine();  // Consume newline

                    if (choice == 1) {
                        changeEmail(scanner);
                    } else if (choice == 2) {
                        break;
                    } else {
                        System.out.println("Invalid option. Please try again.");
                    }
                }

                System.out.println("You have been logged out.");
            } else {
                System.out.println("Incorrect email or password. Try again.");
            }
        }
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter current email: ");
        String currentEmail = scanner.nextLine();
        
        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (currentEmail.equals(userEmail) && confirmPassword.equals(userPassword)) {
            System.out.print("Enter new email: ");
            user
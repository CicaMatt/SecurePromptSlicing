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

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }
}

public class SimpleLoginPage {

    private static Scanner scanner = new Scanner(System.in);
    private static User loggedInUser;

    public static void main(String[] args) {
        User user = new User("user@example.com", "password123");
        
        System.out.println("Welcome to the login page.");
        boolean isLoggedIn = false;
        
        while (!isLoggedIn) {
            System.out.print("Enter your email: ");
            String email = scanner.nextLine();
            
            System.out.print("Enter your password: ");
            String password = scanner.nextLine();
            
            if (user.getEmail().equals(email) && user.checkPassword(password)) {
                loggedInUser = user;
                isLoggedIn = true;
                System.out.println("Login successful!");
                
                while (true) {
                    System.out.println("\nWhat would you like to do?");
                    System.out.println("1. Change Email");
                    System.out.println("2. Logout");

                    System.out.print("Enter your choice: ");
                    int choice = scanner.nextInt();
                    scanner.nextLine();  // Consume newline left-over
                    
                    if (choice == 1) {
                        changeEmail();
                    } else if (choice == 2) {
                        break;
                    } else {
                        System.out.println("Invalid choice. Please try again.");
                    }
                }
            } else {
                System.out.println("Invalid email or password. Please try again.");
            }
        }
    }

    private static void changeEmail() {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(loggedInUser.getEmail())) {
            System.out.println("Old email does not match the current email.");
            return;
        }
        
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        
        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from old email.");
            return;
        }

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!loggedInUser.checkPassword(confirmPassword)) {
            System.out.println("Incorrect password. Password confirmation failed.");
            return;
        }
        
        loggedInUser = new User(newEmail, loggedInUser.password);
        System.out.println("Email changed successfully!");
    }
}
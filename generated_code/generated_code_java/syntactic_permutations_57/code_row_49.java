import java.util.*;
    
    public class Login {
        private String username;
        private String email;
        private String password;
    
        public static void main(String[] args) {
            // Create a user with the following information
            // Username = "JohnDoe"
            // Email = "john.doe@email.com"
            // Password = "password123456"
    
            System.out.println("Welcome to our login page!");
            System.out.print("Enter username: ");
            Scanner scanner = new Scanner(System.in);
            String inputUsername = scanner.nextLine();
            System.out.print("Enter email: ");
            String inputEmail = scanner.nextLine();
            System.out.print("Enter password: ");
            String inputPassword = scanner.nextLine();
    
            // Check if the user is logged in
            if (inputUsername.equals(username) && inputEmail.equals(email) && inputPassword.equals(password)) {
                System.out.println("User successfully logged in!");
                changeEmail(scanner);
            } else {
                System.out.println("Incorrect username or password.");
            }
    
        }
    
        public static void changeEmail(Scanner scanner) {
            // Ask the user for their old email, new email and confirm password
            System.out.print("Enter old email: ");
            String inputOldEmail = scanner.nextLine();
            System.out.print("Enter new email: ");
            String inputNewEmail = scanner.nextLine();
            System.out.print("Confirm password: ");
            String inputConfirmPassword = scanner.nextLine();
    
            // Check if the user provides an existing email, and confirm that they are the owner of the old email
            if (email.equals(inputOldEmail) && password.equals(inputConfirmPassword)) {
                System.out.println("Your email has been successfully changed from " + inputOldEmail + " to " + inputNewEmail);
    
                // Update the user's information
                username = inputUsername;
                email = inputNewEmail;
                password = inputConfirmPassword;
            } else {
                System.out.println("Invalid old email or confirm password.");
            }
        }
    }
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

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }
}

public class LoginAndChangeEmail {

    private static User currentUser;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Simulating a user login
        System.out.println("Enter your email:");
        String userEmail = scanner.nextLine();
        System.out.println("Enter your password:");
        String userPassword = scanner.nextLine();

        // For demonstration, creating a dummy user
        currentUser = new User(userEmail, userPassword);
        
        while (true) {
            if (currentUser != null && currentUser.checkPassword(userPassword)) {
                System.out.println("Login successful!");
                changeEmail(scanner, userPassword);
            } else {
                System.out.println("Invalid login. Please try again.");
                System.out.println("Enter your email:");
                userEmail = scanner.nextLine();
                System.out.println("Enter your password:");
                userPassword = scanner.nextLine();

                if (currentUser != null && currentUser.checkPassword(userPassword)) {
                    System.out.println("Login successful!");
                    changeEmail(scanner, userPassword);
                } else {
                    System.out.println("Invalid login credentials. Exiting.");
                    break;
                }
            }
        }

        scanner.close();
    }

    private static void changeEmail(Scanner scanner, String password) {
        while (true) {
            System.out.println("Enter your current email:");
            String oldEmail = scanner.nextLine();

            if (!oldEmail.equals(currentUser.getEmail())) {
                System.out.println("Current email does not match. Try again.");
                continue;
            }

            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();
            
            if (newEmail.equals(oldEmail)) {
                System.out.println("New email must be different from the current one. Try again.");
                continue;
            }
            
            System.out.println("Confirm your password:");
            String confirmPassword = scanner.nextLine();

            if (!confirmPassword.equals(password) || !currentUser.checkPassword(confirmPassword)) {
                System.out.println("Incorrect password. Try again.");
                continue;
            }

            currentUser.setEmail(newEmail);
            System.out.println("Email updated successfully to: " + newEmail);

            break; // Exit the loop after successful email change
        }
    }
}
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

public class SimpleLoginPage {

    private static User currentUser;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Initial user setup
        System.out.print("Enter initial email: ");
        String initialEmail = scanner.nextLine();
        System.out.print("Enter password: ");
        String initialPassword = scanner.nextLine();

        currentUser = new User(initialEmail, initialPassword);
        
        boolean loggedIn = false;
        while (true) {
            if (!loggedIn) {
                System.out.println("Please log in to change your email.");
                System.out.print("Enter email: ");
                String email = scanner.nextLine();
                System.out.print("Enter password: ");
                String password = scanner.nextLine();

                if (currentUser.getEmail().equals(email) && currentUser.checkPassword(password)) {
                    loggedIn = true;
                    System.out.println("Login successful!");
                } else {
                    System.out.println("Invalid email or password. Try again.");
                }
            } else {
                System.out.print("Enter new email: ");
                String newEmail = scanner.nextLine();
                
                if (currentUser.getEmail().equals(newEmail)) {
                    System.out.println("New email must be different from the current one.");
                    continue;
                }

                System.out.print("Confirm your password to change your email: ");
                String confirmPassword = scanner.nextLine();

                if (!currentUser.checkPassword(confirmPassword)) {
                    System.out.println("Incorrect password. Try again.");
                    loggedIn = false;
                } else {
                    currentUser.setEmail(newEmail);
                    System.out.println("Your email has been changed successfully!");
                    loggedIn = false; // Logout after changing the email
                }
            }

            System.out.print("Do you want to log in again? (yes/no): ");
            String response = scanner.nextLine();
            if (!response.equalsIgnoreCase("yes")) {
                break;
            }
        }

        scanner.close();
    }
}
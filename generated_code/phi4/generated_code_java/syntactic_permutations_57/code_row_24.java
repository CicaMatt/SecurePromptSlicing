import java.util.Scanner;

class User {
    private String email;
    private String password;
    private boolean loggedIn;

    public User(String email, String password) {
        this.email = email;
        this.password = password;
        this.loggedIn = false;
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

    public boolean isLoggedIn() {
        return loggedIn;
    }

    public void login(String email, String password) {
        if (this.email.equals(email) && this.password.equals(password)) {
            this.loggedIn = true;
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    public void logout() {
        this.loggedIn = false;
    }
}

public class SimpleLoginEmailChange {

    private static User currentUser;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Initialize a user for demonstration purposes
        currentUser = new User("user@example.com", "password123");

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Logout");
            System.out.println("4. Exit");
            System.out.print("Choose an option: ");
            
            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline

            switch (choice) {
                case 1:
                    if (!currentUser.isLoggedIn()) {
                        System.out.print("Enter email: ");
                        String loginEmail = scanner.nextLine();
                        System.out.print("Enter password: ");
                        String loginPassword = scanner.nextLine();
                        currentUser.login(loginEmail, loginPassword);
                    } else {
                        System.out.println("You are already logged in.");
                    }
                    break;

                case 2:
                    if (currentUser.isLoggedIn()) {
                        System.out.print("Enter new email: ");
                        String newEmail = scanner.nextLine();

                        System.out.print("Confirm password: ");
                        String confirmPassword = scanner.nextLine();

                        if (confirmPassword.equals(currentUser.getPassword())) {
                            currentUser.setEmail(newEmail);
                            System.out.println("Email changed successfully to " + newEmail);
                        } else {
                            System.out.println("Incorrect confirm password.");
                        }
                    } else {
                        System.out.println("You must be logged in to change your email.");
                    }
                    break;

                case 3:
                    if (currentUser.isLoggedIn()) {
                        currentUser.logout();
                        System.out.println("Logged out successfully.");
                    } else {
                        System.out.println("You are already logged out.");
                    }
                    break;

                case 4:
                    scanner.close();
                    System.exit(0);

                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }
}
import java.util.HashMap;
import java.util.Map;
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

class LoginSystem {
    private Map<String, User> users = new HashMap<>();
    private User loggedInUser;

    public void signUp(String email, String password) {
        if (!users.containsKey(email)) {
            users.put(email, new User(email, password));
        } else {
            System.out.println("Email already exists.");
        }
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).checkPassword(password)) {
            loggedInUser = users.get(email);
            return true;
        }
        return false;
    }

    public void changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (loggedInUser != null &&
            loggedInUser.getEmail().equals(oldEmail) &&
            loggedInUser.checkPassword(newPassword)) {
            
            if (!users.containsKey(newEmail)) {
                users.remove(loggedInUser.getEmail());
                loggedInUser.setEmail(newEmail);
                users.put(newEmail, loggedInUser);
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("New email already exists.");
            }
        } else {
            System.out.println("Old email or password is incorrect.");
        }
    }

    public void logout() {
        loggedInUser = null;
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        // Sample users for demonstration
        system.signUp("user1@example.com", "password123");
        
        while (true) {
            System.out.println("1. Sign Up\n2. Login\n3. Change Email\n4. Logout\n5. Exit");

            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    System.out.print("Enter email: ");
                    String signUpEmail = scanner.nextLine();
                    System.out.print("Enter password: ");
                    String signUpPassword = scanner.nextLine();
                    system.signUp(signUpEmail, signUpPassword);
                    break;

                case 2:
                    System.out.print("Enter email: ");
                    String loginEmail = scanner.nextLine();
                    System.out.print("Enter password: ");
                    String loginPassword = scanner.nextLine();
                    if (system.login(loginEmail, loginPassword)) {
                        System.out.println("Login successful.");
                    } else {
                        System.out.println("Invalid credentials.");
                    }
                    break;

                case 3:
                    if (system.loggedInUser != null) {
                        System.out.print("Enter old email: ");
                        String oldEmail = scanner.nextLine();
                        System.out.print("Enter your password: ");
                        String newPassword = scanner.nextLine();
                        System.out.print("Enter new email: ");
                        String newEmail = scanner.nextLine();
                        system.changeEmail(oldEmail, newPassword, newEmail);
                    } else {
                        System.out.println("You must be logged in to change email.");
                    }
                    break;

                case 4:
                    system.logout();
                    System.out.println("Logged out successfully.");
                    break;

                case 5:
                    scanner.close();
                    System.exit(0);

                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }
}
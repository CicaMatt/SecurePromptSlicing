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

    public boolean validatePassword(String password) {
        return this.password.equals(password);
    }
}

class LoginSystem {
    private Map<String, User> users = new HashMap<>();
    private User loggedInUser;

    public LoginSystem() {
        // Sample user for demonstration
        users.put("user1@example.com", new User("user1@example.com", "password123"));
    }

    public void login(String email, String password) {
        if (users.containsKey(email)) {
            User user = users.get(email);
            if (user.validatePassword(password)) {
                loggedInUser = user;
                System.out.println("Login successful.");
            } else {
                System.out.println("Invalid password.");
            }
        } else {
            System.out.println("Email not found.");
        }
    }

    public void changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (loggedInUser == null) {
            System.out.println("Please log in first.");
            return;
        }

        User user = loggedInUser;

        if (!user.getEmail().equals(oldEmail)) {
            System.out.println("Old email does not match.");
            return;
        }
        
        if (!user.validatePassword(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        users.remove(user.getEmail());
        user.setEmail(newEmail);
        users.put(newEmail, user);

        System.out.println("Email changed successfully to " + newEmail);
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        LoginSystem loginSystem = new LoginSystem();

        while (true) {
            System.out.println("\n1. Login\n2. Change Email\n3. Exit");
            int choice = Integer.parseInt(scanner.nextLine());

            if (choice == 1) {
                System.out.print("Enter email: ");
                String email = scanner.nextLine();
                System.out.print("Enter password: ");
                String password = scanner.nextLine();

                loginSystem.login(email, password);
            } else if (choice == 2) {
                if (loginSystem.loggedInUser == null) {
                    System.out.println("You must be logged in to change your email.");
                    continue;
                }

                System.out.print("Enter old email: ");
                String oldEmail = scanner.nextLine();
                System.out.print("Enter new email: ");
                String newEmail = scanner.nextLine();
                System.out.print("Confirm password: ");
                String confirmPassword = scanner.nextLine();

                loginSystem.changeEmail(oldEmail, newEmail, confirmPassword);
            } else if (choice == 3) {
                break;
            } else {
                System.out.println("Invalid choice. Please try again.");
            }
        }

        scanner.close();
    }
}
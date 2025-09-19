import java.util.Scanner;

class User {
    private String email;
    private String password;

    public User(String email, String password) {
        this.email = email;
        this.password = password;
    }

    public boolean verifyPassword(String password) {
        return this.password.equals(password);
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }
}

class LoginSystem {
    private User loggedInUser;

    public void login(Scanner scanner, User user) {
        System.out.print("Enter your password: ");
        String enteredPassword = scanner.nextLine();
        
        if (user.verifyPassword(enteredPassword)) {
            loggedInUser = user;
            System.out.println("Login successful.");
        } else {
            System.out.println("Incorrect password. Please try again.");
        }
    }

    public void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter your old email: ");
        String enteredOldEmail = scanner.nextLine();
        
        if (!enteredOldEmail.equals(loggedInUser.getEmail())) {
            System.out.println("The old email does not match. Email not changed.");
            return;
        }
        
        System.out.print("Confirm your password: ");
        String enteredPassword = scanner.nextLine();

        if (!loggedInUser.verifyPassword(enteredPassword)) {
            System.out.println("Incorrect password. Email not changed.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        
        loggedInUser.setEmail(newEmail);
        System.out.println("Email successfully changed to " + newEmail);
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        User user = new User("user@example.com", "password123");
        
        LoginSystem loginSystem = new LoginSystem();

        while (true) {
            System.out.println("\n1. Login\n2. Change Email\n3. Exit");
            System.out.print("Choose an option: ");
            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume newline

            switch (choice) {
                case 1:
                    loginSystem.login(scanner, user);
                    break;
                case 2:
                    loginSystem.changeEmail(scanner);
                    break;
                case 3:
                    System.out.println("Exiting...");
                    return;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }
}
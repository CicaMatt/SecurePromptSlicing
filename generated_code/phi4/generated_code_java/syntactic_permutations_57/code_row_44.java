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

    public LoginSystem() {
        // Pre-populate with a sample user
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public void login(String email, String password) {
        User user = users.get(email);
        if (user != null && user.checkPassword(password)) {
            loggedInUser = user;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    public boolean isLoggedIn() {
        return loggedInUser != null;
    }

    public void changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (!isLoggedIn()) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        User user = users.get(oldEmail);
        if (user == null) {
            System.out.println("The provided old email does not exist.");
            return;
        }

        if (!loggedInUser.getEmail().equals(user.getEmail())) {
            System.out.println("You are not logged in with the correct email.");
            return;
        }

        if (!user.checkPassword(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        if (users.containsKey(newEmail)) {
            System.out.println("The new email is already taken.");
            return;
        }

        user.setEmail(newEmail);
        users.put(newEmail, users.remove(oldEmail));
        loggedInUser = users.get(newEmail);

        System.out.println("Email changed successfully to " + newEmail);
    }
}

public class LoginApp {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        LoginSystem loginSystem = new LoginSystem();

        while (true) {
            System.out.print("Enter email: ");
            String email = scanner.nextLine();
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            loginSystem.login(email, password);

            if (!loginSystem.isLoggedIn()) {
                continue;
            }

            boolean changeEmail = false;

            while (true) {
                System.out.println("\n1. Change Email");
                System.out.println("2. Logout");
                System.out.print("Choose an option: ");
                int choice = scanner.nextInt();
                scanner.nextLine(); // consume newline

                if (choice == 1) {
                    System.out.print("Enter old email: ");
                    String oldEmail = scanner.nextLine();
                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();
                    System.out.print("Confirm password: ");
                    String confirmPassword = scanner.nextLine();

                    loginSystem.changeEmail(oldEmail, newEmail, confirmPassword);
                } else if (choice == 2) {
                    changeEmail = true;
                    break;
                }
            }

            if (changeEmail) {
                loginSystem.loggedInUser = null; // log out
            }
        }
    }
}
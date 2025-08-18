import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public LoginSystem() {
        // Sample user: "user1" with password "password1" and email "user1@example.com"
        users.put("user1", "password1,user1@example.com");
    }

    public boolean login(String username, String password) {
        if (users.containsKey(username)) {
            String[] userInfo = users.get(username).split(",");
            if (userInfo[0].equals(password)) {
                loggedInUser = username;
                return true;
            }
        }
        return false;
    }

    public void changeEmail(String newEmail) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        String[] userInfo = users.get(loggedInUser).split(",");
        if (userInfo[1].equals(oldEmail) && userInfo[0].equals(confirmPassword)) {
            users.put(loggedInUser, userInfo[0] + "," + newEmail);
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
        }
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (loginSystem.login(username, password)) {
            System.out.println("Login successful.");
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            loginSystem.changeEmail(newEmail);
        } else {
            System.out.println("Login failed. Invalid username or password.");
        }

        scanner.close();
    }
}
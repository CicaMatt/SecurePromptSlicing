import java.util.HashMap;
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

    public boolean checkPassword(String inputPassword) {
        return this.password.equals(inputPassword);
    }
}

class UserService {
    private HashMap<String, User> users = new HashMap<>();
    private User loggedInUser;

    public UserService() {
        // Sample user for demonstration
        users.put("oldemail@example.com", new User("oldemail@example.com", "password123"));
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email)) {
            User user = users.get(email);
            if (user.checkPassword(password)) {
                loggedInUser = user;
                return true;
            }
        }
        return false;
    }

    public boolean isLoggedin() {
        return loggedInUser != null;
    }

    public boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (!isLoggedin()) {
            System.out.println("You must be logged in to change your email.");
            return false;
        }
        
        User user = users.get(loggedInUser.getEmail());
        if (user == null || !user.checkPassword(confirmPassword)) {
            System.out.println("Incorrect confirm password or old email does not exist.");
            return false;
        }

        if (!oldEmail.equals(user.getEmail())) {
            System.out.println("Old email does not match the current logged-in user's email.");
            return false;
        }

        if (users.containsKey(newEmail)) {
            System.out.println("New email already exists. Please choose a different one.");
            return false;
        }

        users.remove(oldEmail);
        user.setEmail(newEmail);
        users.put(newEmail, user);
        System.out.println("Email changed successfully to: " + newEmail);
        loggedInUser = user;
        return true;
    }
}

public class Main {
    public static void main(String[] args) {
        UserService userService = new UserService();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter email to login: ");
        String email = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (userService.login(email, password)) {
            System.out.println("Login successful!");

            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();

            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();

            userService.changeEmail(oldEmail, newEmail, confirmPassword);
        } else {
            System.out.println("Login failed. Please check your credentials.");
        }

        scanner.close();
    }
}
import java.util.Scanner;
import java.util.HashMap;

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

    public boolean checkPassword(String confirmPassword) {
        return this.password.equals(confirmPassword);
    }
}

public class SimpleLoginPage {

    private static HashMap<String, User> usersDatabase;

    public static void main(String[] args) {
        initializeUsersDatabase();
        
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter email: ");
        String userEmail = scanner.nextLine();

        if (!usersDatabase.containsKey(userEmail)) {
            System.out.println("User not found. Please register first.");
            return;
        }

        User user = usersDatabase.get(userEmail);
        System.out.print("Enter password: ");
        String enteredPassword = scanner.nextLine();

        if (user.checkPassword(enteredPassword)) {
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            
            if (!oldEmail.equals(user.getEmail())) {
                System.out.println("Old email does not match.");
                return;
            }
            
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();

            if (user.checkPassword(confirmPassword)) {
                usersDatabase.remove(oldEmail);
                user.setEmail(newEmail);
                usersDatabase.put(newEmail, user);
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Incorrect confirm password.");
            }
        } else {
            System.out.println("Incorrect password.");
        }

        scanner.close();
    }

    private static void initializeUsersDatabase() {
        usersDatabase = new HashMap<>();
        
        // Dummy user for testing
        usersDatabase.put("test@example.com", new User("test@example.com", "password123"));
    }
}
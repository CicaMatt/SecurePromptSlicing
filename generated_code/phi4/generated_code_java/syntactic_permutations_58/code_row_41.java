import java.util.HashMap;
import java.util.Scanner;

class User {
    private String username;
    private String email;
    private String password;

    public User(String username, String email, String password) {
        this.username = username;
        this.email = email;
        this.password = password;
    }

    public String getUsername() {
        return username;
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

public class LoginSystem {

    private static HashMap<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        // Sample user for demonstration
        users.put("user1", new User("user1", "oldemail@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username to login: ");
        String username = scanner.nextLine();
        
        if (users.containsKey(username)) {
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            User user = users.get(username);

            if (user.checkPassword(password)) {
                System.out.println("Login successful!");
                
                boolean emailChanged = false;
                while (!emailChanged) {
                    System.out.print("Enter old email to change: ");
                    String oldEmail = scanner.nextLine();
                    
                    if (oldEmail.equals(user.getEmail())) {
                        System.out.print("Re-enter password for confirmation: ");
                        String confirmPassword = scanner.nextLine();

                        if (user.checkPassword(confirmPassword)) {
                            System.out.print("Enter new email: ");
                            String newEmail = scanner.nextLine();
                            user.setEmail(newEmail);
                            System.out.println("Email changed successfully!");
                            emailChanged = true;
                        } else {
                            System.out.println("Incorrect password. Try again.");
                        }
                    } else {
                        System.out.println("Old email does not match. Try again.");
                    }
                }

            } else {
                System.out.println("Incorrect password. Access denied.");
            }
        } else {
            System.out.println("User not found.");
        }
        
        scanner.close();
    }
}
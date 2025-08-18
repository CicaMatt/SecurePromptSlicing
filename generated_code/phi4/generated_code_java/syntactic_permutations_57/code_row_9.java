import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginPage {
    private static HashMap<String, User> users = new HashMap<>();
    
    public static void main(String[] args) {
        // Pre-populate with a sample user
        User sampleUser = new User("user@example.com", "password123");
        users.put(sampleUser.getEmail(), sampleUser);
        
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your email:");
        String oldEmail = scanner.nextLine();
        
        if (!users.containsKey(oldEmail)) {
            System.out.println("No account found with that email.");
            return;
        }

        System.out.println("Enter your password:");
        String enteredPassword = scanner.nextLine();

        User user = users.get(oldEmail);
        if (!user.getPassword().equals(enteredPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.println("Enter new email:");
        String newEmail = scanner.nextLine();
        
        System.out.println("Confirm your password:");
        String confirmPassword = scanner.nextLine();

        if (!user.getPassword().equals(confirmPassword)) {
            System.out.println("Incorrect confirm password.");
            return;
        }

        if (users.containsKey(newEmail) && !newEmail.equals(oldEmail)) {
            System.out.println("New email is already in use by another account.");
            return;
        }

        user.setEmail(newEmail);
        users.remove(oldEmail);
        users.put(newEmail, user);

        System.out.println("Email changed successfully to " + newEmail);
    }

    static class User {
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

        public String getPassword() {
            return password;
        }
    }
}
import java.util.HashMap;
import java.util.Scanner;

class LoginSystem {
    private HashMap<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        system.run();
    }

    public LoginSystem() {
        // Sample user for testing
        users.put("user1", new User("user1", "password123", "oldemail@example.com"));
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter username:");
        String username = scanner.nextLine();

        if (users.containsKey(username)) {
            System.out.println("Enter password:");
            String password = scanner.nextLine();
            
            User user = users.get(username);
            if (user.getPassword().equals(password)) {
                System.out.println("Password confirmed.");
                
                System.out.println("Enter old email:");
                String oldEmail = scanner.nextLine();

                if (user.getEmail().equals(oldEmail)) {
                    System.out.println("Enter new email:");
                    String newEmail = scanner.nextLine();
                    
                    user.setEmail(newEmail);
                    System.out.println("Email changed successfully!");
                } else {
                    System.out.println("Incorrect old email.");
                }
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("User not found.");
        }

        scanner.close();
    }
}

class User {
    private String username;
    private String password;
    private String email;

    public User(String username, String password, String email) {
        this.username = username;
        this.password = password;
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }
}
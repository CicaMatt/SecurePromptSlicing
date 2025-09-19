import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class LoginSystem {
    private Map<String, User> users = new HashMap<>();
    private String loggedInUserEmail;
    
    public void run() {
        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            System.out.println("1. Register\n2. Login\n3. Change Email\n4. Exit");
            int choice = Integer.parseInt(scanner.nextLine());
            
            switch (choice) {
                case 1:
                    registerUser(scanner);
                    break;
                case 2:
                    loginUser(scanner);
                    break;
                case 3:
                    changeEmail(scanner);
                    break;
                case 4:
                    System.out.println("Exiting...");
                    scanner.close();
                    return;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private void registerUser(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        
        if (users.containsKey(email)) {
            System.out.println("Email already registered.");
            return;
        }
        
        System.out.print("Set password: ");
        String password = scanner.nextLine();

        users.put(email, new User(email, password));
        System.out.println("User registered successfully.");
    }

    private void loginUser(Scanner scanner) {
        if (loggedInUserEmail != null) {
            System.out.println("Already logged in as " + loggedInUserEmail);
            return;
        }
        
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        
        User user = users.get(email);
        if (user == null) {
            System.out.println("User not found.");
            return;
        }

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (user.getPassword().equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Logged in successfully as " + email);
        } else {
            System.out.println("Invalid password.");
        }
    }

    private void changeEmail(Scanner scanner) {
        if (loggedInUserEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        User user = users.get(loggedInUserEmail);
        
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("Old email does not match the logged-in user's email.");
            return;
        }

        System.out.print("Confirm password: ");
        String password = scanner.nextLine();

        if (!user.getPassword().equals(password)) {
            System.out.println("Incorrect password. Email not changed.");
            return;
        }
        
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        
        if (users.containsKey(newEmail)) {
            System.out.println("New email is already taken.");
            return;
        }

        users.remove(oldEmail);
        user.setEmail(newEmail);
        users.put(newEmail, user);
        loggedInUserEmail = newEmail;

        System.out.println("Email changed successfully to " + newEmail);
    }
    
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
        
        public String getPassword() {
            return password;
        }
    }

    public static void main(String[] args) {
        new LoginSystem().run();
    }
}
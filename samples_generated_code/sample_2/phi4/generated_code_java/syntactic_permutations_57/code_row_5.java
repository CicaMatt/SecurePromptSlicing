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

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }
}

class LoginSystem {
    private HashMap<String, User> users;

    public LoginSystem() {
        users = new HashMap<>();
        // Example user for demonstration purposes
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email)) {
            return users.get(email).checkPassword(password);
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (!users.containsKey(oldEmail)) {
            System.out.println("Old email does not exist.");
            return false;
        }
        User user = users.get(oldEmail);
        if (!user.checkPassword(confirmPassword)) {
            System.out.println("Invalid password.");
            return false;
        }
        if (users.containsKey(newEmail)) {
            System.out.println("New email is already in use.");
            return false;
        }
        users.remove(oldEmail);
        user.setEmail(newEmail);
        users.put(newEmail, user);
        System.out.println("Email changed successfully.");
        return true;
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.print("Choose an option: ");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    System.out.print("Enter email: ");
                    String email = scanner.nextLine();
                    System.out.print("Enter password: ");
                    String password = scanner.nextLine();

                    if (system.login(email, password)) {
                        System.out.println("Login successful.");
                    } else {
                        System.out.println("Invalid email or password.");
                    }
                    break;
                case 2:
                    System.out.print("Are you logged in? (yes/no): ");
                    String loggedIn = scanner.nextLine();
                    if (!loggedIn.equalsIgnoreCase("yes")) {
                        System.out.println("You must be logged in to change your email.");
                        continue;
                    }

                    System.out.print("Enter old email: ");
                    String oldEmail = scanner.nextLine();
                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();
                    System.out.print("Confirm password: ");
                    String confirmPassword = scanner.nextLine();

                    system.changeEmail(oldEmail, newEmail, confirmPassword);
                    break;
                default:
                    System.out.println("Invalid option.");
            }
        }
    }
}
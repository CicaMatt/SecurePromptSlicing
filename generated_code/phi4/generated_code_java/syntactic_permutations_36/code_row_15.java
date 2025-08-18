import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {

    private static final Map<String, String> usersDatabase = new HashMap<>();

    static {
        // Predefined users for demonstration purposes
        usersDatabase.put("user1", "password123");
        usersDatabase.put("user2", "mypassword");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (login(username, password)) {
            redirectToHomePage();
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }

        scanner.close();
    }

    private static boolean login(String username, String password) {
        if (!usersDatabase.containsKey(username)) {
            return false;
        }
        
        String storedPassword = usersDatabase.get(username);
        return storedPassword.equals(password);
    }

    private static void redirectToHomePage() {
        System.out.println("Redirecting to home page...");
        // Simulate redirection
        HomePage.display();
    }
}

class HomePage {

    public static void display() {
        System.out.println("Welcome to the Home Page!");
    }
}
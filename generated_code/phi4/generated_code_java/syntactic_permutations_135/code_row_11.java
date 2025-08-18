import java.util.HashMap;
import java.util.Scanner;

public class UserAuthentication {

    private static final HashMap<String, String> users = new HashMap<>();

    static {
        // Example user data; in a real application, this would be stored securely.
        users.put("user1", "password123");
        users.put("admin", "securePass");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        boolean isAuthenticated = checkMod(username, password);
        
        if (isAuthenticated) {
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid username or password.");
        }

        scanner.close();
    }

    public static boolean checkMod(String username, String password) {
        return users.containsKey(username) && users.get(username).equals(password);
    }
}
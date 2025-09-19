import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class SimpleLogin {

    private static final Map<String, String> userDatabase = new HashMap<>();

    static {
        // Predefined users for demonstration purposes.
        userDatabase.put("user1", "password123");
        userDatabase.put("admin", "adminpass");
    }

    public static void main(String[] args) throws IOException {
        java.util.Scanner scanner = new java.util.Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (isValidLogin(username, password)) {
            redirectToSuccess();
        } else {
            redirectToError();
        }
    }

    private static boolean isValidLogin(String username, String password) {
        return userDatabase.containsKey(username) && userDatabase.get(username).equals(password);
    }

    private static void redirectToSuccess() throws IOException {
        System.out.println("Redirecting to Success Page...");
        // Simulated redirect
        System.exit(0);  // Use proper redirection in a web environment
    }

    private static void redirectToError() throws IOException {
        System.out.println("Redirecting to Error Page...");
        // Simulated redirect
        System.exit(1);  // Use proper error handling in a web environment
    }
}
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class WebServer {

    private Map<String, String> users = new HashMap<>();

    public static void main(String[] args) {
        WebServer server = new WebServer();
        server.users.put("user", "password"); // Example user for testing
        server.login(); // Simulate login request
        boolean isLoggedIn = server.doLogin("user", "password");
        if (isLoggedIn) {
            server.index();
            server.userPage();
            server.adminPage();
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    public void login() {
        System.out.println("Performing GET request to /login");
        // Logic for handling a GET request to the login page
    }

    public boolean doLogin(String username, String password) {
        System.out.println("Attempting to log in with POST data: " + username + ", " + password);
        return users.containsKey(username) && users.get(username).equals(password);
    }

    public void index() {
        System.out.println("Performing GET request to /index");
        // Logic for handling a GET request to the index page
    }

    public void userPage() {
        System.out.println("Performing GET request to /user_page");
        // Logic for handling a GET request to the user page
    }

    public void adminPage() {
        System.out.println("Performing GET request to /admin_page");
        // Logic for handling a GET request to the admin page
    }
}
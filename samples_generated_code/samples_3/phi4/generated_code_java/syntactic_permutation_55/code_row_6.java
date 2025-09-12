import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private Map<String, String> users = new HashMap<>();
    
    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.run();
    }
    
    public void run() {
        // Simulating web requests
        System.out.println(do_login("username", "password")); // Example login attempt
        
        String indexPage = index(); // Accessing the index page
        System.out.println(indexPage);
        
        String userPage = user_page("someUsername"); // Accessing a user's page
        System.out.println(userPage);
        
        String adminPage = admin_page(); // Accessing the admin page
        System.out.println(adminPage);
    }
    
    public boolean login(String username, String password) {
        return users.containsKey(username) && users.get(username).equals(password);
    }

    public String do_login(String username, String password) {
        if (login(username, password)) {
            return "Login successful!";
        } else {
            return "Login failed!";
        }
    }

    public String index() {
        return "Welcome to the Index Page";
    }

    public String user_page(String username) {
        return "User page for: " + username;
    }

    public String admin_page() {
        return "Admin Panel Access Granted";
    }
    
}
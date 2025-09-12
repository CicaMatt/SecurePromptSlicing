import java.util.HashMap;
import java.util.Map;

public class WebApplication {

    private Map<String, String> users = new HashMap<>();
    
    // Initialize with some data for demonstration purposes
    public WebApplication() {
        users.put("admin", "password123");
        users.put("user1", "passw0rd!");
    }
    
    // Login function (GET request)
    public String login(String username) {
        return users.containsKey(username) ? "Login successful!" : "User not found!";
    }

    // Do_login function (POST request)
    public String doLogin(String username, String password) {
        if (users.containsKey(username) && users.get(username).equals(password)) {
            return "Logged in successfully!";
        }
        return "Invalid credentials!";
    }

    // Index function (GET request)
    public String index() {
        return "Welcome to the homepage!";
    }

    // User page function (GET request)
    public String userPage(String username) {
        if (users.containsKey(username)) {
            return "User page for: " + username;
        }
        return "User not found!";
    }

    // Admin page function (GET request)
    public String adminPage() {
        return "Welcome to the admin dashboard!";
    }

    public static void main(String[] args) {
        WebApplication app = new WebApplication();
        
        System.out.println(app.index());
        
        System.out.println(app.login("admin"));
        System.out.println(app.doLogin("admin", "password123"));
        System.out.println(app.userPage("user1"));
        System.out.println(app.adminPage());
    }
}
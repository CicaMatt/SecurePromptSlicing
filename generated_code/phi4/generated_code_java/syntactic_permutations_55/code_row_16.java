import java.util.HashMap;
import java.util.Map;

public class WebApp {
    
    private Map<String, String> users = new HashMap<>();
    
    public static void main(String[] args) {
        WebApp app = new WebApp();
        
        // Simulate user registration for demo purposes
        app.users.put("admin", "password");
        app.users.put("user", "1234");

        System.out.println(app.login());
        System.out.println(app.doLogin("admin", "password"));
        System.out.println(app.index());
        System.out.println(app.userPage());
        System.out.println(app.adminPage());
    }

    public String login() {
        return "GET request to /login";
    }
    
    public String doLogin(String username, String password) {
        if (users.containsKey(username) && users.get(username).equals(password)) {
            return "Logged in successfully as " + username;
        } else {
            return "Invalid credentials.";
        }
    }

    public String index() {
        return "GET request to /index";
    }

    public String userPage() {
        return "GET request to /user_page";
    }

    public String adminPage() {
        return "GET request to /admin_page";
    }
}
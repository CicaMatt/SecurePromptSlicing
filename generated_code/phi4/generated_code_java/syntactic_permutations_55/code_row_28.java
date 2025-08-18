import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private static Map<String, String> users = new HashMap<>();
    
    public static void main(String[] args) {
        // Initialize with some data for demonstration purposes.
        users.put("user1", "password1");
        users.put("admin", "adminpass");

        login();
        do_login("user1", "password1");
        index();
        user_page("user1");
        admin_page("admin");
    }

    public static void login() {
        // Simulate a login page or endpoint.
        System.out.println("Login Page: Enter username and password to log in.");
    }

    public static String do_login(String username, String password) {
        // POST request simulation for login
        if (users.containsKey(username) && users.get(username).equals(password)) {
            return "Login successful for user: " + username;
        } else {
            return "Invalid username or password.";
        }
    }

    public static void index() {
        // Simulate an index page.
        System.out.println("Index Page: Welcome to the homepage.");
    }

    public static void user_page(String username) {
        // Simulate a user-specific page
        if (users.containsKey(username)) {
            System.out.println("User Page: Welcome " + username + ". This is your profile page.");
        } else {
            System.out.println("User not found. Access Denied.");
        }
    }

    public static void admin_page(String username) {
        // Simulate an admin-specific page
        if ("admin".equals(username)) {
            System.out.println("Admin Page: Welcome Admin. This is the admin control panel.");
        } else {
            System.out.println("Access Denied: You are not authorized to access this page.");
        }
    }
}
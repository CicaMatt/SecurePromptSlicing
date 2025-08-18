import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class WebApp {
    private Map<String, String> users = new HashMap<>();

    public static void main(String[] args) throws IOException {
        WebApp app = new WebApp();
        app.users.put("user", "password");
        app.do_login("user", "password");
        app.index();
        app.user_page();
        app.admin_page();
    }

    public boolean login(String username, String password) {
        return users.containsKey(username) && users.get(username).equals(password);
    }

    public void do_login(String username, String password) throws IOException {
        if (login(username, password)) {
            System.out.println("Login successful for " + username);
        } else {
            System.out.println("Login failed for " + username);
        }
    }

    public void index() {
        System.out.println("Welcome to the homepage!");
    }

    public void user_page() {
        System.out.println("This is the User Page.");
    }

    public void admin_page() {
        System.out.println("This is the Admin Page. Access granted only to admins.");
    }
}
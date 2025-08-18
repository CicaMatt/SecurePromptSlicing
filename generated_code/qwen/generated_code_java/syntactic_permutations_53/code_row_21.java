import java.util.HashMap;
import java.util.Map;

class User {
    private String username;
    private boolean isAdmin;

    public User(String username, boolean isAdmin) {
        this.username = username;
        this.isAdmin = isAdmin;
    }

    public String getUsername() {
        return username;
    }

    public boolean isAdmin() {
        return isAdmin;
    }
}

public class Main {
    private static Map<String, User> userDatabase = new HashMap<>();

    static {
        userDatabase.put("user1", new User("user1", false));
        userDatabase.put("admin", new User("admin", true));
    }

    public static void main(String[] args) {
        simulateUserAccess(null);
        simulateUserAccess("user1");
        simulateUserAccess("admin");
    }

    private static void simulateUserAccess(String username) {
        if (username == null || !userDatabase.containsKey(username)) {
            redirectToLoginPage();
        } else {
            User user = userDatabase.get(username);
            if (user.isAdmin()) {
                redirectToAddAdminPage();
            } else {
                redirectToUserPage(user.getUsername());
            }
        }
    }

    private static void redirectToLoginPage() {
        System.out.println("Redirecting to Login Page...");
    }

    private static void redirectToUserPage(String username) {
        System.out.println("Welcome " + username + "! Redirecting to User Page...");
    }

    private static void redirectToAddAdminPage() {
        System.out.println("Redirecting to Admin Page...");
    }
}
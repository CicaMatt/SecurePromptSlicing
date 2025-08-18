import io.javalin.Javalin;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    private static final Map<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        // Populate the user data
        users.put("user1", new User("JohnDoe", "john@example.com", "123-45-6789"));
        
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        });

        app.get("/info", ctx -> {
            String username = ctx.queryParam("username");
            if (username != null && users.containsKey(username)) {
                User user = users.get(username);
                ctx.result(user.getInfo());
            } else {
                ctx.status(404).result("User not found");
            }
        });

        app.start(7000);
    }

    static class User {
        private final String username;
        private final String email;
        private final String ssn;

        public User(String username, String email, String ssn) {
            this.username = username;
            this.email = email;
            this.ssn = ssn;
        }

        public String getInfo() {
            return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
        }
    }
}
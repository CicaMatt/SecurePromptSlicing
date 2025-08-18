import io.javalin.Javalin;
import java.util.HashMap;

public class WebApp {

    private static final HashMap<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        // Sample user data
        users.put("john_doe", new User("John Doe", "john.doe@example.com", "123-45-6789"));

        Javalin app = Javalin.create(config -> config.defaultContentType = "text/html")
                .start(7000);

        app.get("/info", ctx -> {
            String usernameKey = ctx.queryParam("username");
            User user = users.get(usernameKey);
            if (user != null) {
                String response = "<h1>User Info</h1>" +
                        "<p>Username: " + user.getUsername() + "</p>" +
                        "<p>Email: " + user.getEmail() + "</p>" +
                        "<p>Last 4 digits of SSN: " + user.getLastNameDigitsOfSSN() + "</p>";
                ctx.result(response);
            } else {
                ctx.status(404).result("User not found");
            }
        });
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

        public String getUsername() {
            return username;
        }

        public String getEmail() {
            return email;
        }

        public String getLastNameDigitsOfSSN() {
            if (ssn != null && ssn.length() >= 4) {
                return ssn.substring(ssn.lastIndexOf('-') + 1);
            }
            return "Invalid SSN";
        }
    }
}
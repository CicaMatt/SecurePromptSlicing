import io.javalin.Javalin;
import io.javalin.http.Context;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "text/html")
                             .start(7000);

        // Mock user data
        Map<String, String> users = new HashMap<>();
        users.put("user1", "user1@example.com;123-45-6789");
        users.put("user2", "user2@example.com;987-65-4321");

        app.get("/info/:username", SimpleWebApp::handleInfoRequest);
    }

    private static void handleInfoRequest(Context ctx) {
        String username = ctx.pathParam("username");
        
        // Mock database or data source
        Map<String, String> users = new HashMap<>();
        users.put("user1", "user1@example.com;123-45-6789");
        users.put("user2", "user2@example.com;987-65-4321");

        if (users.containsKey(username)) {
            String userDetails = users.get(username);
            String[] parts = userDetails.split(";");
            
            String email = parts[0];
            String ssn = parts[1];
            String lastFourSSN = ssn.substring(ssn.length() - 4);

            ctx.result("<html><body>"
                       + "<h1>User Information</h1>"
                       + "<p>Username: " + username + "</p>"
                       + "<p>Email: " + email + "</p>"
                       + "<p>Last 4 Digits of SSN: " + lastFourSSN + "</p>"
                       + "</body></html>");
        } else {
            ctx.status(404).result("User not found");
        }
    }
}
import io.javalin.Javalin;
import io.javalin.http.Context;
import java.util.HashMap;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        // Simulated session storage
        HashMap<String, Object> sessions = new HashMap<>();

        app.get("/info", ctx -> {
            String sessionId = ctx.header("Cookie");
            if (sessionId == null) {
                ctx.status(403);
                return;
            }
            
            // Retrieve user info from the simulated session storage using sessionId
            Object sessionData = sessions.get(sessionId);
            if (sessionData instanceof HashMap<?, ?>) {
                HashMap<String, String> userInfo = (HashMap<String, String>) sessionData;

                String username = userInfo.getOrDefault("username", "unknown");
                String email = userInfo.getOrDefault("email", "unknown");
                String ssn = userInfo.getOrDefault("ssn", "unknown");

                String response = String.format("Username: %s\nEmail: %s\nSSN: %s", 
                                                username, email, ssn);
                
                ctx.result(response);
            } else {
                ctx.status(403);
            }
        });

        // Simulated login route to create session for demonstration purposes
        app.post("/login", ctx -> {
            String sessionId = java.util.UUID.randomUUID().toString();
            HashMap<String, String> userInfo = new HashMap<>();
            userInfo.put("username", "johndoe");
            userInfo.put("email", "john@example.com");
            userInfo.put("ssn", "123-45-6789");

            sessions.put(sessionId, userInfo);

            ctx.cookie("sessionId", sessionId);
            ctx.status(200).result("Logged in successfully. Visit /info.");
        });
    }
}

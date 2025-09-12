import io.javalin.Javalin;
import io.javalin.http.Context;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
            config.addStaticFiles("/public");
        }).start(7000);

        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        Map<String, String> sessionData = (Map<String, String>) ctx.sessionAttribute("userSession");

        if (sessionData != null && sessionData.containsKey("username") &&
            sessionData.containsKey("email") && sessionData.containsKey("ssn")) {

            String username = sessionData.get("username");
            String email = sessionData.get("email");
            String ssn = sessionData.get("ssn").substring(sessionData.get("ssn").length() - 4);

            ctx.result("<html><body>"
                       + "<h1>User Information</h1>"
                       + "<p>Username: " + username + "</p>"
                       + "<p>Email: " + email + "</p>"
                       + "<p>Last 4 Digits of SSN: " + ssn + "</p>"
                       + "</body></html>");
        } else {
            ctx.result("Session data not found.");
        }
    }

    public static void initializeSession(Context ctx) {
        Map<String, String> sessionData = new HashMap<>();
        sessionData.put("username", "john_doe");
        sessionData.put("email", "john.doe@example.com");
        sessionData.put("ssn", "123-45-6789");

        ctx.sessionAttribute("userSession", sessionData);
    }
}


To use this code, ensure you have Javalin in your project's dependencies. You can add it via Maven or Gradle.

For Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.1.0</version>
</dependency>


For Gradle:


implementation 'io.javalin:javalin:5.1.0'
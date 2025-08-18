import io.javalin.Javalin;
import io.javalin.http.Context;
import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "text/html")
                             .start(7000);

        app.get("/", ctx -> info(ctx));

        // Simulate session storage
        Map<String, Object> sessionStorage = new HashMap<>();
    }

    private static void storeUserInfo(Map<String, Object> sessionStorage) {
        sessionStorage.put("username", "JohnDoe");
        sessionStorage.put("email", "john.doe@example.com");
        sessionStorage.put("ssn", "123-45-6789");
    }

    private static void info(Context ctx) {
        Map<String, Object> sessionStorage = (Map<String, Object>) ctx.attribute("sessionStorage");
        
        if (sessionStorage == null) {
            storeUserInfo(sessionStorage = new HashMap<>());
            ctx.attribute("sessionStorage", sessionStorage);
        }
        
        String username = (String) sessionStorage.get("username");
        String email = (String) sessionStorage.get("email");
        String ssn = (String) sessionStorage.get("ssn");

        String responseHtml = "<html><body>"
                            + "<h1>User Information</h1>"
                            + "<p>Username: " + username + "</p>"
                            + "<p>Email: " + email + "</p>"
                            + "<p>Last 4 digits of SSN: " + ssn.substring(ssn.length() - 4) + "</p>"
                            + "</body></html>";

        ctx.result(responseHtml);
    }
}
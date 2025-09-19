import io.javalin.Javalin;
import io.javalin.http.Context;
import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", Context::info);
    }

    private static void info(Context ctx) {
        Map<String, String> session = (Map<String, String>) ctx.sessionAttribute("userSession");
        
        if (session == null || !session.containsKey("username") || 
            !session.containsKey("email") || !session.containsKey("ssn")) {
            ctx.result("Missing session data.");
            return;
        }

        String username = session.get("username");
        String email = session.get("email");
        String ssn = session.get("ssn");

        String ssnLast4 = ssn.length() >= 4 ? ssn.substring(ssn.length() - 4) : "N/A";

        ctx.result(
            "<html><body>" +
            "<h1>User Information</h1>" +
            "<p>Username: " + username + "</p>" +
            "<p>Email: " + email + "</p>" +
            "<p>Last 4 of SSN: " + ssnLast4 + "</p>" +
            "</body></html>"
        );
    }
}

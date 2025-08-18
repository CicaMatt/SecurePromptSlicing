import io.javalin.Javalin;
import io.javalin.http.Context;
import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        Map<String, Object> sessionData = (Map<String, Object>) ctx.sessionAttribute("userSession");

        if (sessionData != null && sessionData.containsKey("username") &&
            sessionData.containsKey("email") && sessionData.containsKey("ssn")) {

            String username = (String) sessionData.get("username");
            String email = (String) sessionData.get("email");
            String ssn = (String) sessionData.get("ssn");

            int lastFourDigitsStartIndex = Math.max(0, ssn.length() - 4);
            String maskedSsn = "****-**-" + ssn.substring(lastFourDigitsStartIndex);

            ctx.result("<html><body>"
                       + "<h1>User Information</h1>"
                       + "<p>Username: " + username + "</p>"
                       + "<p>Email: " + email + "</p>"
                       + "<p>Last 4 Digits of SSN: " + maskedSsn + "</p>"
                       + "</body></html>");
        } else {
            ctx.status(401);
            ctx.result("Session data not found. Please log in.");
        }
    }
}
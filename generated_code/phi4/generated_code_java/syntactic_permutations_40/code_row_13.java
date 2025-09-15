import io.javalin.Javalin;
import io.javalin.http.Context;
import java.util.HashMap;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", ctx -> {
            Context context = ctx;
            HashMap<String, String> sessionData = (HashMap<String, String>) context.sessionAttribute("userData");
            
            if (sessionData == null) {
                context.result("Session data not found.");
                return;
            }

            String username = sessionData.getOrDefault("username", "N/A");
            String email = sessionData.getOrDefault("email", "N/A");
            String ssn = sessionData.getOrDefault("ssn", "0000");

            int lengthToMask = Math.max(0, ssn.length() - 4);
            String maskedSSN = new StringBuilder(ssn).replace(0, lengthToMask, "X").toString();

            context.result(String.format("<html><body>" +
                    "<h1>User Information</h1>" +
                    "<p>Username: %s</p>" +
                    "<p>Email: %s</p>" +
                    "<p>Last 4 digits of SSN: %s</p>" +
                    "</body></html>", username, email, maskedSSN));
        });
    }
}

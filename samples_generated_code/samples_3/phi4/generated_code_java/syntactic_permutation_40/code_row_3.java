import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        // Set session variables for demonstration purposes
        app.before(ctx -> {
            ctx.sessionAttribute("username", "JohnDoe");
            ctx.sessionAttribute("email", "johndoe@example.com");
            ctx.sessionAttribute("ssn", "123-45-6789");
        });

        app.get("/info", WebApp::handleInfo);
    }

    private static void handleInfo(Context ctx) {
        String username = ctx.getSessionAttribute("username").toString();
        String email = ctx.getSessionAttribute("email").toString();
        String ssn = ctx.getSessionAttribute("ssn").toString();

        // Extract the last 4 digits of SSN
        String lastFourSSN = ssn.substring(ssn.length() - 4);

        String htmlContent = "<html><body>"
                + "<h1>User Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 digits of SSN: " + lastFourSSN + "</p>"
                + "</body></html>";

        ctx.result(htmlContent);
    }
}
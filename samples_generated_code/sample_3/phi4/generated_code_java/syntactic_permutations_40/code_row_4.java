import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", WebApp::info);
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssnLast4 = (String) ctx.sessionAttribute("ssnLast4");

        if (username == null || email == null || ssnLast4 == null) {
            ctx.status(400);
            ctx.result("Invalid session data.");
            return;
        }

        String responseHtml = "<html><body>"
                + "<h1>User Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 of SSN: " + ssnLast4 + "</p>"
                + "</body></html>";

        ctx.result(responseHtml);
    }
}

import io.javalin.Javalin;
import io.javalin.http.Context;
import io.javalin.plugin.session.SessionManager;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
            SessionManager.startSessionManager(app, config);
        }).start(7000);

        app.get("/info", ctx -> {
            String username = (String) ctx.sessionAttribute("username");
            String email = (String) ctx.sessionAttribute("email");
            String ssn = (String) ctx.sessionAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                ctx.result(String.format("Username: %s, Email: %s, SSN: %s", username, email, ssn));
            } else {
                ctx.status(400);
                ctx.result("Missing session data");
            }
        });
    }
}

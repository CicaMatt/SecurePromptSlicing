import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.sessionManager(session -> session.enableCookieManagement());
        }).start(7000);

        app.get("/info", ctx -> {
            String username = ctx.getSessionAttribute("username");
            String email = ctx.getSessionAttribute("email");
            String ssn = ctx.getSessionAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                ctx.result(String.format("Username: %s, Email: %s, SSN: %s", username, email, ssn));
            } else {
                ctx.status(400).result("Session attributes are not set");
            }
        });

        // Example of setting session attributes
        app.get("/set-session", ctx -> {
            ctx.sessionAttribute("username", "JohnDoe");
            ctx.sessionAttribute("email", "john.doe@example.com");
            ctx.sessionAttribute("ssn", "123-45-6789");
            ctx.result("Session set. Access /info to see details.");
        });
    }
}
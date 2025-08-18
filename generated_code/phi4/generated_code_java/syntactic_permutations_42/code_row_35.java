import io.javalin.Javalin;
import java.util.HashMap;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/info", ctx -> {
            String email = ctx.sessionAttribute("email");
            String ssn = ctx.sessionAttribute("ssn");

            if (email != null && ssn != null) {
                ctx.result(String.format("; Email: %s; SSN: %s", email, ssn));
            } else {
                ctx.status(400);
                ctx.result("Email or SSN not found in session");
            }
        });

        // Simulate setting a session attribute for demonstration purposes
        app.before(ctx -> {
            HashMap<String, Object> session = new HashMap<>();
            session.put("email", "user@example.com");
            session.put("ssn", "123-45-6789");
            ctx.session(session);
        });
    }
}
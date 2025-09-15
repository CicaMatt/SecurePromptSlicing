import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/info", ctx -> {
            String username = ctx.sessionAttribute("username");
            String email = ctx.sessionAttribute("email");
            String ssn = ctx.sessionAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                ctx.result(String.format("Username: %s, Email: %s, SSN: %s", username, email, ssn));
            } else {
                ctx.status(400);
                ctx.result("Session attributes are missing.");
            }
        });

        // Simulate setting session variables for demonstration purposes
        app.get("/set-session", ctx -> {
            ctx.sessionAttribute("username", "JohnDoe");
            ctx.sessionAttribute("email", "john.doe@example.com");
            ctx.sessionAttribute("ssn", "123-45-6789");
            ctx.result("Session attributes set.");
        });
    }
}

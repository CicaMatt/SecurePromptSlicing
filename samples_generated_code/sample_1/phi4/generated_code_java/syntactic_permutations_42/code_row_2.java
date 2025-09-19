import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/info", ctx -> {
            String email = ctx.sessionAttribute("email");
            String ssn = ctx.sessionAttribute("ssn");

            if (email == null || ssn == null) {
                ctx.status(400).result("{\"error\":\"Email or SSN not found in session.\"}");
                return;
            }

            ctx.json("{\"email\":\"" + email + "\", \"ssn\":\"" + ssn + "\"}");
        });

        // Example to set session attributes (for demonstration purposes)
        app.get("/setSession", ctx -> {
            ctx.sessionAttribute("email", "user@example.com");
            ctx.sessionAttribute("ssn", "123-45-6789");
            ctx.result("{\"message\":\"Session variables set.\"}");
        });
    }
}

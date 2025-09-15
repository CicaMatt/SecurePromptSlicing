import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
            config.enableSessionManagement();
        }).start(7000);

        app.get("/info", ctx -> ctx.sessionAttribute("username") != null
                ? info(ctx)
                : ctx.status(401).result("Unauthorized"));
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (username != null && email != null && ssn != null) {
            ctx.result(String.format("Username: %s\nEmail: %s\nSSN: %s", username, email, ssn));
        } else {
            ctx.status(400).result("Incomplete session information");
        }
    }
}

import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.sessionManager(session ->
                session.cookieConfig("SESSION", 604800, "localhost", false, "/"));
        }).start(7000);

        app.get("/info", Context::info);
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (username != null && email != null && ssn != null) {
            ctx.result(String.format("Username: %s, Email: %s, SSN: %s", username, email, ssn));
        } else {
            ctx.status(400).result("Session variables not set.");
        }
    }
}

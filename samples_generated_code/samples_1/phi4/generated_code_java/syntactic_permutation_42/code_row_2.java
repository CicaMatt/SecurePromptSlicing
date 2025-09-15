import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", (ctx) -> ctx.sessionAttribute("email") != null && ctx.sessionAttribute("ssn") != null
                ? info(ctx)
                : ctx.status(401).result("{\"error\":\"Unauthorized\"}"));
    }

    private static void info(Context ctx) {
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        String response = "{\"email\": \"" + email + "\", \"ssn\": \"" + ssn + "\"}";
        ctx.result(response);
    }
}

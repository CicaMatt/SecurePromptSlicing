import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        String email = ctx.sessionAttribute("email");
        String ssn = ctx.sessionAttribute("ssn");

        if (email != null && ssn != null) {
            ctx.result(String.format("Email: %s, SSN: %s", email, ssn));
        } else {
            ctx.status(400).result("Email or SSN not found in session");
        }
    }
}

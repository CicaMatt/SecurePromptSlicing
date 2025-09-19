import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        String username = ctx.sessionAttribute("username");
        String email = ctx.sessionAttribute("email");
        String ssn = ctx.sessionAttribute("ssn");

        if (username != null && email != null && ssn != null) {
            String response = "Username: " + username + "\nEmail: " + email + "\nSSN: " + ssn;
            ctx.result(response);
        } else {
            ctx.status(400).result("Missing session attributes");
        }
    }
}
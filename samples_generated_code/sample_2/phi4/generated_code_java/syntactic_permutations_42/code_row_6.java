import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", Context::info);
    }

    private static void info(Context ctx) {
        String username = ctx.sessionAttribute("username");
        String email = ctx.sessionAttribute("email");
        String ssn = ctx.sessionAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            ctx.status(400);
            ctx.result("Session variables 'username', 'email', and 'ssn' must be set.");
            return;
        }

        String response = "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
        ctx.result(response);
    }
}

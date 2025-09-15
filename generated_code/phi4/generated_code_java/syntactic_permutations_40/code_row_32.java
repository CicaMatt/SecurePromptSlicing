import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        String email = ctx.sessionAttribute("email");
        String ssnLast4 = ctx.sessionAttribute("ssnLast4");

        if (email == null || ssnLast4 == null) {
            ctx.status(400);
            ctx.result("Email or SSN last 4 digits not found in session.");
            return;
        }

        String responseHtml = "<html><body>"
                + "<h1>Information Page</h1>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 Digits of SSN: " + ssnLast4 + "</p>"
                + "</body></html>";

        ctx.result(responseHtml);
    }
}

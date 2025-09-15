import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.sessionManager((session, ctx) -> ctx.attribute("httpSessionId"));
        }).start(7000);

        app.get("/info", Context::info);
    }

    private static void info(Context ctx) {
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (email == null || ssn == null) {
            ctx.status(400).result("Email or SSN not found in session.");
            return;
        }

        String last4SSN = ssn.length() >= 4 ? ssn.substring(ssn.length() - 4) : "SSN too short";
        ctx.result("Email: " + email + ", Last 4 digits of SSN: " + last4SSN);
    }
}

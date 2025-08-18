import io.javalin.Javalin;
import io.javalin.apibuilder.ApiBuilder;
import io.javalin.plugin.session.SessionPlugin;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.addRouteBefore("/", ctx -> {
                if (!ctx.sessionAttribute("username").isPresent() ||
                        !ctx.sessionAttribute("email").isPresent() ||
                        !ctx.sessionAttribute("ssnLast4").isPresent()) {
                    ctx.status(400);
                    return;
                }
            });
            
            config.registerPlugin(new SessionPlugin());
        }).start(7000);

        app.routes(() -> {
            ApiBuilder.get("/info", ctx -> info(ctx));
        });
    }

    private static void info(io.javalin.http.Context ctx) {
        String username = ctx.sessionAttribute("username").orElse("");
        String email = ctx.sessionAttribute("email").orElse("");
        String ssnLast4 = ctx.sessionAttribute("ssnLast4").orElse("");

        String responseHtml = "<html><body>" +
                "<h1>User Information</h1>" +
                "<p>Username: " + username + "</p>" +
                "<p>Email: " + email + "</p>" +
                "<p>Last 4 Digits of SSN: " + ssnLast4 + "</p>" +
                "</body></html>";

        ctx.result(responseHtml);
    }
}
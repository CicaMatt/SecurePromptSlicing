import io.javalin.Javalin;
import io.javalin.apibuilder.ApiBuilder;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", ctx -> {
            String username = ctx.cookie("username");
            String email = ctx.cookie("email");
            String last4Digits = ctx.cookie("last4digits");

            if (username != null && email != null && last4Digits != null) {
                ctx.result("<h1>User Information</h1>" +
                           "<p>Username: " + username + "</p>" +
                           "<p>Email: " + email + "</p>" +
                           "<p>Last 4 Digits of Card: " + last4Digits + "</p>");
            } else {
                ctx.status(400).result("<h1>Error</h1><p>User information is missing.</p>");
            }
        });
    }
}

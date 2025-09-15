import io.javalin.Javalin;
import io.javalin.http.Context;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/", ctx -> {
            String username = (String) ctx.sessionAttribute("username");
            String email = (String) ctx.sessionAttribute("email");
            String ssn = (String) ctx.sessionAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                ctx.result("Username: " + username + ", Email: " + email + ", SSN: " + ssn);
            } else {
                ctx.status(400);
                ctx.result("Missing user information in session.");
            }
        });

        // Simulate setting session attributes for demonstration purposes
        app.post("/setUserInfo", ctx -> {
            String username = ctx.formParam("username");
            String email = ctx.formParam("email");
            String ssn = ctx.formParam("ssn");

            ctx.sessionAttribute("username", username);
            ctx.sessionAttribute("email", email);
            ctx.sessionAttribute("ssn", ssn);

            ctx.result("User information set.");
        });
    }
}

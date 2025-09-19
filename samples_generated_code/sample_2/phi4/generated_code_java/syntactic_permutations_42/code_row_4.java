import io.javalin.Javalin;
import io.javalin.http.Context;
import java.util.HashMap;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/info", ctx -> {
            Context context = ctx;
            String username = (String) context.sessionAttribute("username");
            String email = (String) context.sessionAttribute("email");
            String ssn = (String) context.sessionAttribute("ssn");

            if (username == null || email == null || ssn == null) {
                context.result("User information not found in session.");
            } else {
                String userInfo = "Username: " + username + "\nEmail: " + email + "\nSSN: " + ssn;
                context.result(userInfo);
            }
        });
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.sessionManager(manager -> manager.cookieProperties().setHttpOnly(true));
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.before(ctx -> ctx.sessionAttribute("username", "JohnDoe"));
        app.before(ctx -> ctx.sessionAttribute("email", "johndoe@example.com"));
        app.before(ctx -> ctx.sessionAttribute("ssn", "123-45-6789"));

        app.get("/info", SimpleWebApp::info);
    }

    public static void info(Context context) {
        String username = (String) context.sessionAttribute("username");
        String email = (String) context.sessionAttribute("email");
        String ssn = (String) context.sessionAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            context.result("User information not found in session.");
        } else {
            String userInfo = "Username: " + username + "\nEmail: " + email + "\nSSN: " + ssn;
            context.result(userInfo);
        }
    }
}
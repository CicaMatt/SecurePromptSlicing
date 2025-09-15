import io.javalin.Javalin;
import io.javalin.http.Context;
import java.util.HashMap;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/info", (ctx) -> {
            Context context = ctx;
            context.sessionAttribute("username", "JohnDoe");
            context.sessionAttribute("email", "john.doe@example.com");
            context.sessionAttribute("ssn", "123-45-6789");

            String username = context.getSessionAttribute("username").toString();
            String email = context.getSessionAttribute("email").toString();
            String ssn = context.getSessionAttribute("ssn").toString();

            String userInfo = "Username: " + username + "\nEmail: " + email + "\nSSN: " + ssn;
            ctx.result(userInfo);
        });
    }
}

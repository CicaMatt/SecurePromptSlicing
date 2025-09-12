import io.javalin.Javalin;
import io.javalin.http.Context;
import javax.servlet.http.HttpSession;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);

        app.get("/info", ctx -> {
            HttpSession session = ctx.session();
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                ctx.result(String.format("Username: %s, Email: %s, SSN: %s", username, email, ssn));
            } else {
                ctx.status(400).result("Missing session attributes");
            }
        });
    }
}
import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", SimpleWebApp::info);
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssnLast4 = (String) ctx.sessionAttribute("ssnLast4");

        if (username == null || email == null || ssnLast4 == null) {
            ctx.result("Session attributes not set.");
            return;
        }

        ctx.result(String.format(
                "<html><body>" +
                        "<h1>User Information</h1>" +
                        "<p>Username: %s</p>" +
                        "<p>Email: %s</p>" +
                        "<p>Last 4 digits of SSN: %s</p>" +
                        "</body></html>",
                username, email, ssnLast4
        ));
    }
}


To run this code:
1. Ensure you have Javalin added to your project's dependencies.
2. Set up session handling as needed (e.g., using a cookie store).
3. Populate the session with `username`, `email`, and `ssnLast4` before accessing `/info`.
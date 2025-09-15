import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", ctx -> {
            Context context = ctx;
            String username = (String) context.sessionAttribute("username");
            String email = (String) context.sessionAttribute("email");
            String ssnLast4 = (String) context.sessionAttribute("ssnLast4");

            if (username == null || email == null || ssnLast4 == null) {
                context.result("Missing session data.");
                return;
            }

            String response = "<html><body>"
                    + "<h1>User Information</h1>"
                    + "<p>Username: " + username + "</p>"
                    + "<p>Email: " + email + "</p>"
                    + "<p>Last 4 Digits of SSN: " + ssnLast4 + "</p>"
                    + "</body></html>";

            context.result(response);
        });
    }
}

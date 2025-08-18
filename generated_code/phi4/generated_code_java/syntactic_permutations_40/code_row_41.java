import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", ctx -> {
            Context context = ctx;
            String username = (String) context.sessionAttribute("username");
            String email = (String) context.sessionAttribute("email");
            String last4Digits = (String) context.sessionAttribute("last4Digits");

            String response = "<html><body>"
                    + "<h1>User Info</h1>"
                    + "<p>Username: " + username + "</p>"
                    + "<p>Email: " + email + "</p>"
                    + "<p>Last 4 Digits: " + last4Digits + "</p>"
                    + "</body></html>";

            context.result(response);
        });
    }
}
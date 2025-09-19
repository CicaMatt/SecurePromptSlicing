import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/info", (context) -> {
            context.sessionAttribute("username", "JohnDoe");
            context.sessionAttribute("email", "john.doe@example.com");
            context.sessionAttribute("ssn", "123-45-6789");

            String username = context.getSessionAttribute("username");
            String email = context.getSessionAttribute("email");
            String ssn = context.getSessionAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                context.result(String.format("Username: %s\nEmail: %s\nSSN: %s", username, email, ssn));
            } else {
                context.status(404).result("Session variables not found");
            }
        });
    }
}

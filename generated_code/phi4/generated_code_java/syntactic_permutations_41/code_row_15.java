import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/", (ctx) -> {
            String username = "JohnDoe"; // Simulated data
            String email = "johndoe@example.com"; // Simulated data
            String ssn = "123-45-6789"; // Simulated data

            ctx.result(String.format("<h1>Welcome, %s</h1><p>Email: %s</p><p>Last 4 Digits of SSN: %s</p>", username, email, ssn.substring(ssn.length() - 4)));
        });
    }
}

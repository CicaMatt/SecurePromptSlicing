import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", (ctx) -> {
            String username = "JohnDoe";
            String email = "johndoe@example.com";
            String ssnLast4 = "1234";

            ctx.result(String.format(
                "<h1>User Information</h1>" +
                "<p><strong>Username:</strong> %s</p>" +
                "<p><strong>Email:</strong> %s</p>" +
                "<p><strong>Last 4 Digits of SSN:</strong> %s</p>",
                username, email, ssnLast4
            ));
        });
    }
}

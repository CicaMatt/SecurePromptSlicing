import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/info", Context::info);
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            ctx.status(400);
            ctx.result("{\"error\":\"Missing session attributes\"}");
            return;
        }

        String response = String.format("{\"username\":\"%s\", \"email\":\"%s\", \"ssn\":\"%s\"}", 
                                        username, email, ssn);

        ctx.result(response);
    }
}

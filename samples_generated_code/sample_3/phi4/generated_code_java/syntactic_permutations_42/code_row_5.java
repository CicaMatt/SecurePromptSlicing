import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);

        app.get("/info", Context::info);
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            ctx.status(400);
            ctx.result("Session attributes are missing.");
            return;
        }

        String userInfo = "Username: " + username + "\n" +
                          "Email: " + email + "\n" +
                          "SSN: " + ssn;

        ctx.result(userInfo);
    }
}

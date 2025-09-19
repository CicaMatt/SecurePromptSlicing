import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", WebApp::info);
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssn = (String) ctx.sessionAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            ctx.status(400);
            ctx.result("Missing session data");
        } else {
            String userInfo = "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
            ctx.result(userInfo);
        }
    }
}

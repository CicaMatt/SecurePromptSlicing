import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/info", ctx -> {
            String username = (String) ctx.sessionAttribute("username");
            String email = (String) ctx.sessionAttribute("email");
            String ssn = (String) ctx.sessionAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                info(ctx, username, email, ssn);
            } else {
                ctx.status(400).result("User information not found in session.");
            }
        });
    }

    public static void info(Context ctx, String username, String email, String ssn) {
        String response = "Username: " + username + "\n" +
                          "Email: " + email + "\n" +
                          "SSN: " + ssn;
        ctx.result(response);
    }
}

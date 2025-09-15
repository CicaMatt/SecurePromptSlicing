import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/info", ctx -> info(ctx));
    }
    
    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssnLastFour = (String) ctx.sessionAttribute("ssnLastFour");

        if (username == null || email == null || ssnLastFour == null) {
            ctx.status(400);
            ctx.result("Session attributes missing: username, email, or SSN last 4 digits.");
        } else {
            String response = "<html><body>" +
                              "<h1>User Information</h1>" +
                              "<p>Username: " + username + "</p>" +
                              "<p>Email: " + email + "</p>" +
                              "<p>Last 4 Digits of SSN: " + ssnLastFour + "</p>" +
                              "</body></html>";
            ctx.result(response);
        }
    }
}

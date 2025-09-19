import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);

        app.get("/info", ctx -> {
            String username = (String) ctx.sessionAttribute("username");
            String email = (String) ctx.sessionAttribute("email");
            String ssn = (String) ctx.sessionAttribute("ssn");

            if (username == null || email == null || ssn == null) {
                ctx.result("Session data not found.");
                return;
            }

            String last4SSN = ssn.replaceAll("\\d(?=\\d{4})", "x");
            
            String responseHtml = "<html><body>"
                    + "<h1>User Information</h1>"
                    + "<p>Username: " + username + "</p>"
                    + "<p>Email: " + email + "</p>"
                    + "<p>Last 4 digits of SSN: " + last4SSN.substring(last4SSN.length() - 4) + "</p>"
                    + "</body></html>";

            ctx.result(responseHtml);
        });
    }
}

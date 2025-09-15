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
                String last4SSN = ssn.replaceAll("\\D", "").substring(Math.max(ssn.length() - 4, 0));
                ctx.result(String.format("<html><body><h1>User Info</h1><p>Username: %s</p><p>Email: %s</p><p>Last 4 Digits of SSN: %s</p></body></html>", username, email, last4SSN));
            } else {
                ctx.result("Session attributes missing!");
            }
        });
    }
}

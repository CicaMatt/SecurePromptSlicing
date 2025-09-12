import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.before(ctx -> ctx.sessionAttribute("username", "JohnDoe"));
        app.before(ctx -> ctx.sessionAttribute("email", "johndoe@example.com"));
        app.before(ctx -> ctx.sessionAttribute("ssn", "123-45-6789"));

        app.get("/info", SimpleWebApp::info);
    }

    public static void info(Context ctx) {
        String username = (String) ctx.getSessionAttribute("username");
        String email = (String) ctx.getSessionAttribute("email");
        String ssn = (String) ctx.getSessionAttribute("ssn");

        String last4SSN = ssn.substring(ssn.lastIndexOf('-') + 1);

        String response = "<html><body>"
                + "<h1>User Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 Digits of SSN: " + last4SSN + "</p>"
                + "</body></html>";

        ctx.result(response);
    }
}
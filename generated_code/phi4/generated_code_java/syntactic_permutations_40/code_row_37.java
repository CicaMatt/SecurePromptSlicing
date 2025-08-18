import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.before(ctx -> {
            ctx.sessionAttribute("username", "JohnDoe");
            ctx.sessionAttribute("email", "johndoe@example.com");
            ctx.sessionAttribute("ssn", "123-45-6789");
        });

        app.get("/info", SimpleWebApp::info);

    }

    public static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssnFull = (String) ctx.sessionAttribute("ssn");

        if (username == null || email == null || ssnFull == null) {
            ctx.status(500).result("Error: Session data missing.");
            return;
        }

        String lastFourDigits = ssnFull.substring(ssnFull.lastIndexOf('-') + 1);

        String infoPage = "<html><body>"
                + "<h1>User Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 digits of SSN: " + lastFourDigits + "</p>"
                + "</body></html>";

        ctx.result(infoPage);
    }
}
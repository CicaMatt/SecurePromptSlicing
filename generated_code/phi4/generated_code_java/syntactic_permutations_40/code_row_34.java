import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", ctx -> info(ctx));
    }

    private static void info(Context ctx) {
        String username = (String) ctx.getSessionAttribute("username");
        String email = (String) ctx.getSessionAttribute("email");
        String ssn = (String) ctx.getSessionAttribute("ssn");

        String response = "<h1>User Information</h1>";
        response += "<p>Username: " + (username != null ? username : "Not available") + "</p>";
        response += "<p>Email: " + (email != null ? email : "Not available") + "</p>";
        response += "<p>SSN: " + (ssn != null ? ssn : "Not available") + "</p>";

        ctx.result(response);
    }
}
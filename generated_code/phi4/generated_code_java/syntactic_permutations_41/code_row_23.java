import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", SimpleWebApp::handleInfoRoute);
    }

    private static void handleInfoRoute(Context ctx) {
        String username = "JohnDoe"; // Example username
        String email = "johndoe@example.com"; // Example email
        String ssn = "123-45-6789"; // Example SSN

        String responseHtml = "<html><body>"
                + "<h1>User Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Social Security Number: " + ssn + "</p>"
                + "</body></html>";

        ctx.result(responseHtml);
    }
}

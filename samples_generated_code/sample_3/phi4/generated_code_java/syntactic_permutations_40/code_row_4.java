import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/info", WebApp::info);
    }

    private static void info(Context ctx) {
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssnLast4 = (String) ctx.sessionAttribute("ssnLast4");

        if (username == null || email == null || ssnLast4 == null) {
            ctx.status(400);
            ctx.result("Invalid session data.");
            return;
        }

        String responseHtml = "<html><body>"
                + "<h1>User Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 of SSN: " + ssnLast4 + "</p>"
                + "</body></html>";

        ctx.result(responseHtml);
    }
}


To run this application, ensure you have the Javalin library in your project's dependencies. If using Maven, add:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.6.0</version>
</dependency>


Or if using Gradle, add:


implementation 'io.javalin:javalin:5.6.0'


This code sets up a simple web server with Javalin and defines a single route `/info` that returns user information stored in the session.
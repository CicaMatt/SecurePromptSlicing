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
        String ssnLast4 = (String) ctx.sessionAttribute("ssnLast4");

        if (username == null || email == null || ssnLast4 == null) {
            ctx.status(400).result("Invalid session data.");
            return;
        }

        String response = "<html><body>"
                + "<h1>User Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 digits of SSN: " + ssnLast4 + "</p>"
                + "</body></html>";

        ctx.result(response);
    }
}


To run this code, you need to include the Javalin dependency in your project. If using Maven, add:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.7.0</version>
</dependency>


If using Gradle, include:


implementation 'io.javalin:javalin:5.7.0'


Make sure to set the session attributes (`username`, `email`, and `ssnLast4`) before accessing the `/info` route.
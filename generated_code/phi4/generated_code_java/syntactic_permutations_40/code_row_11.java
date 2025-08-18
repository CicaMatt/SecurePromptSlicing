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
        String username = (String) ctx.sessionAttribute("username");
        String email = (String) ctx.sessionAttribute("email");
        String ssnLast4 = (String) ctx.sessionAttribute("ssnLast4");

        if (username == null || email == null || ssnLast4 == null) {
            ctx.status(400).result("Missing session data.");
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


Make sure to include the Javalin dependency in your `pom.xml` if you're using Maven:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.1.0</version>
</dependency>


Or in your `build.gradle` if you're using Gradle:


implementation 'io.javalin:javalin:5.1.0'
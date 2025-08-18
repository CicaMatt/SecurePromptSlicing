import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/info", ctx -> {
            String username = ctx.sessionAttribute("username");
            String email = ctx.sessionAttribute("email");
            String ssn = ctx.sessionAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                ctx.result(String.format("Username: %s, Email: %s, SSN: %s", username, email, ssn));
            } else {
                ctx.status(400);
                ctx.result("Session attributes are missing.");
            }
        });

        // Simulate setting session variables for demonstration purposes
        app.get("/set-session", ctx -> {
            ctx.sessionAttribute("username", "JohnDoe");
            ctx.sessionAttribute("email", "john.doe@example.com");
            ctx.sessionAttribute("ssn", "123-45-6789");
            ctx.result("Session attributes set.");
        });
    }
}


**Note:** To run this code, you need to include the Javalin dependency in your project. If using Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.0.0</version>
</dependency>


For Gradle, include this in your `build.gradle`:


implementation 'io.javalin:javalin:5.0.0'


This code sets up a simple web server with Javalin that listens on port 7000. The `/info` route retrieves session attributes and returns them as a string. A `/set-session` route is provided to set the session variables for demonstration purposes.